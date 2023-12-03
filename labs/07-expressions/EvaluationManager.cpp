#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Node.h"
#include "EvaluationManager.h"
#include "Expression.h"
#include "Exceptions.h"
#include "Namespace.h"

std::vector<std::shared_ptr<Namespace>> EvaluationManager::namespacesPtrVector;
std::shared_ptr<Namespace> EvaluationManager::currentNamespacePtr;

void EvaluationManager::evaluate_expression(std::vector<std::string> elements)
{
	std::string command = elements[0];
	std::string name = elements[1];

	try
	{
		if (command == "namespace")
		{
			if (elements[1] == "list")
			{
				EvaluationManager::list_namespaces();
			}
			else if (elements[1] == "create")
			{
				EvaluationManager::create_namespace(elements[2]);
			}
			else if (elements[1] == "use")
			{
				EvaluationManager::use_namespace(elements[2]);
			}
		}
		else if (command == "set")
		{
			if (elements[2] != "=")
			{
				throw NonSpecificException();
			}

			std::string possibleNamespace = find_namespace_in_text(name);
			std::shared_ptr<Namespace> namespaceTemp = nullptr;

			if (possibleNamespace != "")
			{
				namespaceTemp = find_namespace(possibleNamespace);
			}

			auto expressionPtr = find_ptr_for_set(name);

			expressionPtr->set_expression(elements, namespaceTemp);
		}
		else if (command == "unset")
		{
			auto expressionPtr = find_ptr(name);

			if (!expressionPtr)
			{
				throw NonSpecificException();
			}
			else
			{
				auto it = std::find_if(EvaluationManager::currentNamespacePtr->expressionsVector.begin(), EvaluationManager::currentNamespacePtr->expressionsVector.end(),
					[&expressionPtr](const std::shared_ptr<Expression>& e)
					{
						return e == expressionPtr;
					});

				if (it != EvaluationManager::currentNamespacePtr->expressionsVector.end())
				{
					EvaluationManager::currentNamespacePtr->expressionsVector.erase(it);
				}
			}
		}
		else if (command == "evaluate")
		{
			auto expressionPtr = find_ptr(name);

			if (!expressionPtr)
			{
				throw NonSpecificException();
			}
			else
			{
				expressionPtr->evaluate();
				expressionPtr->print_result();
			}

		}
		else if (command == "print")
		{
			auto expressionPtr = find_ptr(name);
			if (!expressionPtr)
			{
				throw NonSpecificException();
			}
			else
			{
				expressionPtr->print_expression();
				std::cout << std::endl;
			}
		}
		else if (command == "copy")
		{
			auto expressionPtr = find_ptr(name);

			if (!expressionPtr)
			{
				throw NonSpecificException();
			}
			else
			{
				expressionPtr->copy_expression(elements[2]);
			}

		}
		else if (command == "rename")
		{
			auto expressionPtr = find_ptr(name);

			if (!expressionPtr)
			{
				throw NonSpecificException();
			}
			else
			{
				std::string renameValue = elements[2];
				expressionPtr->rename_expression(renameValue);
			}

		}
		else
		{
			throw NonSpecificException();
		}
	}
	catch (const CustomException& e)
	{
		std::cout << e.what() << std::endl;
	}
}

std::shared_ptr<Expression> EvaluationManager::find_expression(const std::string& name, std::shared_ptr<Namespace> namespacePtr)
{
	for (auto& exp : namespacePtr->expressionsVector)
	{
		if (exp->variable == name)
		{
			return exp;
		}
	}
	return nullptr;
}

std::shared_ptr<Expression> EvaluationManager::find_expression_or_create_in_namespace(const std::string& name, std::shared_ptr<Namespace> namespacePtr)
{
	auto expressionPtr = find_expression(name, namespacePtr);

	if (!expressionPtr)
	{
		expressionPtr = std::make_shared<Expression>();
		expressionPtr->variable = name;
		expressionPtr->expressionNodePtr = std::make_shared<UnaryNode>(expressionPtr->variable);

		namespacePtr->expressionsVector.push_back(expressionPtr);
	}

	return expressionPtr;
}


std::shared_ptr<Namespace> EvaluationManager::find_namespace(const std::string& name)
{
	try
	{
		for (auto& nmspc : namespacesPtrVector)
		{
			if (nmspc->name == name)
			{
				return nmspc;
			}
		}
		throw NamespaceNotFoundException(name);
	}
	catch (const CustomException& e)
	{
		std::cout << e.what() << std::endl;
	}

	return nullptr;
}

void EvaluationManager::create_namespace(std::string& name)
{
	auto namespacePtr = std::make_shared<Namespace>();
	namespacePtr->name = name;

	namespacesPtrVector.push_back(namespacePtr);
}

void EvaluationManager::use_namespace(std::string& name)
{
	auto namespaceTemp = find_namespace(name);

	currentNamespacePtr = namespaceTemp;
}

void EvaluationManager::list_namespaces()
{
	std::sort(namespacesPtrVector.begin(), namespacesPtrVector.end(),
		[](const std::shared_ptr<Namespace>& a, const std::shared_ptr<Namespace>& b)
		{
			return a->name < b->name;
		});
	for (const auto& ns : namespacesPtrVector)
	{
		std::cout << ns->name << std::endl;
	}
}

std::string EvaluationManager::find_namespace_in_text(std::string name)
{
	std::string possibleNamespace = "";

	std::size_t pos = name.find('.');
	if (pos != std::string::npos)
	{
		possibleNamespace = name.substr(0, pos);
	}
	return possibleNamespace;
}

std::string EvaluationManager::getNameValue(const std::string& fullName)
{
	std::size_t dotPos = fullName.find('.');
	if (dotPos != std::string::npos)
	{
		return fullName.substr(dotPos + 1);
	}
	else
	{
		return fullName;
	}
}

std::shared_ptr<Expression> EvaluationManager::find_ptr(const std::string& name)
{
	std::string possibleNamespace = find_namespace_in_text(name);
	std::shared_ptr<Namespace> namespaceTemp = nullptr;

	if (possibleNamespace != "")
	{
		namespaceTemp = find_namespace(possibleNamespace);
	}

	std::shared_ptr<Expression> expressionPtr;

	if (namespaceTemp)
	{
		auto tempName = EvaluationManager::getNameValue(name);
		expressionPtr = EvaluationManager::find_expression(tempName, namespaceTemp);
	}
	else
	{
		expressionPtr = EvaluationManager::find_expression(name, EvaluationManager::currentNamespacePtr);
	}

	return expressionPtr;
}

std::shared_ptr<Expression> EvaluationManager::find_ptr_for_set(const std::string& name)
{
	std::string possibleNamespace = find_namespace_in_text(name);
	std::shared_ptr<Expression> expressionPtr;
	std::shared_ptr<Namespace> namespaceTemp = nullptr;

	if (possibleNamespace != "")
	{
		namespaceTemp = find_namespace(possibleNamespace);
	}

	if (namespaceTemp)
	{
		auto tempName = EvaluationManager::getNameValue(name);
		expressionPtr = EvaluationManager::find_expression_or_create_in_namespace(tempName, namespaceTemp);
	}
	else
	{
		expressionPtr = EvaluationManager::find_expression_or_create_in_namespace(name, EvaluationManager::currentNamespacePtr);
	}

	try
	{
		if (!expressionPtr)
		{
			throw NonSpecificException();
		}
	}
	catch (const CustomException& e)
	{
		std::cout << e.what() << std::endl;
	}

	return expressionPtr;
}
