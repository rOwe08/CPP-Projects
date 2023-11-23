#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Node.h"
#include "EvaluationManager.h"
#include "Expression.h"

std::shared_ptr<std::vector<Expression>> EvaluationManager::expressionsPtr = std::make_shared<std::vector<Expression>>();

void EvaluationManager::evaluate_expression(std::vector<std::string> elements)
{
	std::string command = elements[0];
	std::string name = elements[1];
	Expression* expressionPtr = nullptr;

	for (Expression& tempExp : *expressionsPtr)
	{
		if (tempExp.variable == name)
		{
			expressionPtr = &tempExp;
			break;
		}
	}

	if (!expressionPtr)
	{
		expressionsPtr->emplace_back();
		expressionsPtr->back().variable = name;

		expressionPtr = &expressionsPtr->back();
	}

	if (command == "set")
	{
		expressionPtr->set_expression(elements);
	}
	else if (command == "unset")
	{
		expressionPtr->unset_expression();
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
		expressionPtr->copy_expression();
	}
	else if (command == "rename")
	{
		std::string renameValue = elements[2];
		expressionPtr->rename_expression(renameValue);
	}
}

Expression* EvaluationManager::find_expression(const std::string& name)
{
	if (expressionsPtr)
	{
		for (auto& exp : *expressionsPtr)
		{
			if (exp.variable == name)
			{
				return &exp;
			}
		}
	}
	return nullptr;
}

void EvaluationManager::set_expressionsPtr(std::shared_ptr<std::vector<Expression>> expressionsPtrTemp)
{
	expressionsPtr = expressionsPtrTemp;
}