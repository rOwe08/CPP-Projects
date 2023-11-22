#include "Node.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

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
		Expression newExpression;
		newExpression.variable = name;

		expressions.push_back(newExpression);
		expressionPtr = &expressions.back();
	}

	std::unique_ptr<Node> root(expressionPtr->create_tree(elements));

	std::string result = expressionPtr->evaluate_tree(root.get());

	if (command == "set")
	{
		expressionPtr->set_expression();
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