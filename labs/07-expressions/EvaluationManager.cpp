#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Node.h"
#include "EvaluationManager.h"
#include "Expression.h"
#include "Namespace.h"

std::vector<std::shared_ptr<Namespace>> EvaluationManager::namespacesPtrVector;
std::shared_ptr<Namespace> EvaluationManager::currentNamespacePtr;

void EvaluationManager::evaluate_expression(std::vector<std::string> elements)
{
	if (elements[0] == "namespace")
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
	else
	{
		std::string command = elements[0];
		std::string name = elements[1];

		std::shared_ptr<Expression> expressionPtr = nullptr;

		std::string possibleNamespace = find_namespace_in_text(name);

		auto namespaceTemp = find_namespace(possibleNamespace);                 ////// if is null!!!!!!!!!!!???????????

		if (namespaceTemp)
		{
			name = EvaluationManager::getNameValue(name);
			expressionPtr = find_expression_in_namespace(name, namespaceTemp);
		}
		else
		{
			expressionPtr = find_expression_in_namespace(name, EvaluationManager::currentNamespacePtr);
		}

		if (command == "set")
		{
			expressionPtr->set_expression(elements, namespaceTemp);
		}
		else if (command == "unset")
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
		else if (command == "evaluate")
		{
			expressionPtr->evaluate();
			expressionPtr->print_result();
		}
		else if (command == "print")
		{
			expressionPtr->print_expression();
			std::cout << std::endl;
		}
		else if (command == "copy")
		{
			expressionPtr->copy_expression(elements[2]);
		}
		else if (command == "rename")
		{
			std::string renameValue = elements[2];
			expressionPtr->rename_expression(renameValue);
		}
		else
		{
			std::cout << "Invalid command";
		}
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

std::shared_ptr<Expression> EvaluationManager::find_expression_in_namespace(const std::string& name, std::shared_ptr<Namespace> namespacePtr)
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
	for (auto& nmspc : namespacesPtrVector)
	{
		if (nmspc->name == name)
		{
			return nmspc;
		}
	}
	return nullptr;
}

void EvaluationManager::create_namespace(std::string& name)
{
	auto namespaceTemp = find_namespace(name);

	if (!namespaceTemp)
	{
		auto namespacePtr = std::make_shared<Namespace>();
		namespacePtr->name = name;

		namespacesPtrVector.push_back(namespacePtr);
	}
	else
	{
		// case where the namespace already exists
	}
}

void EvaluationManager::use_namespace(std::string& name)
{
	auto namespaceTemp = find_namespace(name);

	if (namespaceTemp)
	{
		currentNamespacePtr = namespaceTemp;
	}
	else
	{
		throw std::runtime_error("Namespace '" + name + "' does not exist!");
	}
}

void EvaluationManager::list_namespaces()
{
	for (const auto& ns : namespacesPtrVector)
	{
		std::cout << ns->name << std::endl;
	}
}

std::string EvaluationManager::find_namespace_in_text(std::string name)
{
	std::string possibleNamespace;

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
