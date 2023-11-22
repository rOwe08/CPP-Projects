#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Node.h"
#include "EvaluationManager.h"
#include "Expression.h"

void evaluate_expression(std::vector<std::string> elements, std::vector<Expression>& expressions)
{
	std::string command = elements[0];
	std::string name = elements[1];
	Expression* expressionPtr = nullptr;

	for (Expression& tempExp : expressions)
	{
		if (tempExp.variable == name)
		{
			expressionPtr = &tempExp;
			break;
		}
	}

	if (!expressionPtr)
	{
		expressions.emplace_back();
		expressions.back().variable = name;
		expressionPtr = &expressions.back();
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