#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Node.h"
#include "EvaluationManager.h"
#include "Expression.h"

std::vector<std::shared_ptr<Expression>> EvaluationManager::expressionsVector;

void EvaluationManager::evaluate_expression(std::vector<std::string> elements)
{
	std::string command = elements[0];
	std::string name = elements[1];
	std::shared_ptr<Expression> expressionPtr = nullptr;

	expressionPtr = find_expression(name);

	if (!expressionPtr)
	{
		expressionPtr = std::make_shared<Expression>();
		expressionPtr->variable = name;

		expressionsVector.push_back(expressionPtr);
	}

	if (command == "set")
	{
		//std::cout << "Setting pointers:" << std::endl;
		expressionPtr->set_expression(elements);
		//std::cout << expressionPtr->variable << ": " << expressionPtr << std::endl;

		//std::cout << "Pointers in vector:" << std::endl;
		//printExpressionPointers();
	}
	else if (command == "unset")
	{
		auto it = std::find_if(expressionsVector.begin(), expressionsVector.end(),
			[&expressionPtr](const std::shared_ptr<Expression>& e)
			{
				return e == expressionPtr;
			});

		if (it != expressionsVector.end())
		{
			expressionsVector.erase(it);
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
		//std::cout << expressionPtr->variable << ": " << expressionPtr << std::endl;
		expressionPtr->rename_expression(renameValue);
	}
	//std::cout << std::endl;
}

std::shared_ptr<Expression> EvaluationManager::find_expression(const std::string& name)
{
	for (auto& exp : expressionsVector)
	{
		if (exp->variable == name)
		{
			return exp;
		}
	}
	return nullptr;
}

void EvaluationManager::printExpressionPointers()
{
	for (const auto& exprPtr : EvaluationManager::expressionsVector)
	{
		std::cout << "Pointer Address: " << exprPtr.get() << std::endl;
	}
}