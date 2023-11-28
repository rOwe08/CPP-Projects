#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Node.h"
#include "Expression.h"
#include "EvaluationManager.h"

void Expression::evaluate()
{
    expressionNodePtr->evaluate_node();
    result = expressionNodePtr->result;
}

void Expression::print_result()
{
    std::cout << std::to_string(result) << std::endl;
}

void Expression::print_expression()
{
    expressionNodePtr->print_node();
} 

void Expression::set_expression(std::vector<std::string>& elements)
{
    std::string name = elements[1];
    std::string symbol = elements[3];
    std::shared_ptr<UnaryNode> root;          //////////

    auto expressionPtrRoot = EvaluationManager::find_expression(name);

    if (!expressionPtrRoot)
    {
        root = std::make_shared<UnaryNode>(name);          //////////
    }
    else
    {
        if (expressionPtrRoot->expressionNodePtr)
        {
            root = expressionPtrRoot->expressionNodePtr;
        }
        else
        {
            root = std::make_shared<UnaryNode>(name);
        }
    }

    if (symbol == "-" || symbol == "+" || symbol == "/" || symbol == "*")
    {
        std::shared_ptr<BinaryNode> child;

        if (symbol == "+")
        {
            child = std::make_shared<AdditionNode>(symbol);
        }
        else if (symbol == "-")
        {
            child = std::make_shared<SubtractionNode>(symbol);
        }
        else if (symbol == "/")
        {
            child = std::make_shared<DivisionNode>(symbol);
        }
        else if (symbol == "*")
        {
            child = std::make_shared<MultiplicationNode>(symbol);
        }

        try
        {
            int value = std::stoi(elements[4]);
            child->left = std::make_shared<ConstNode>(elements[4]);
        }
        catch (...)
        {

            auto expressionPtr = EvaluationManager::find_expression(elements[4]);

            if (!expressionPtr)
            {
                expressionPtr = std::make_shared<Expression>();
                expressionPtr->variable = elements[4];

                ///std::cout << expressionPtr->variable << ": " << expressionPtr << std::endl;

                expressionPtr->expressionNodePtr = std::make_shared<UnaryNode>(elements[4]);
                EvaluationManager::expressionsVector.push_back(expressionPtr);
            }

            child->left = expressionPtr->expressionNodePtr;
            //std::cout << child->left->element << ": " << child->left << std::endl;
        }

        try
        {
            int value = std::stoi(elements[5]);
            child->right = std::make_shared<ConstNode>(elements[5]);
        }
        catch (...)
        {

            auto expressionPtr = EvaluationManager::find_expression(elements[5]);

            if (!expressionPtr)
            {
                expressionPtr = std::make_shared<Expression>();
                expressionPtr->variable = elements[5];

                //std::cout << expressionPtr->variable << ": " << expressionPtr << std::endl;

                expressionPtr->expressionNodePtr = std::make_shared<UnaryNode>(elements[5]);

                EvaluationManager::expressionsVector.push_back(expressionPtr);
            }

            child->right = expressionPtr->expressionNodePtr;
        }

        root->child = child;

        expressionNodePtr = root;
    }
    else
    {
        std::shared_ptr<UnaryNode> child;

        try
        {
            int value = std::stoi(symbol);
            child = std::make_shared<ConstNode>(symbol);
        }
        catch (...)
        {
            child = std::make_shared<UnaryNode>(symbol);
        }

        root->child = child;

        expressionNodePtr = root;
    }
}

void Expression::copy_expression(std::string& targetName)
{
    auto copiedExpr = std::make_shared<Expression>();
    copiedExpr->variable = targetName;

    copiedExpr->expressionNodePtr = expressionNodePtr;

    EvaluationManager::expressionsVector.push_back(copiedExpr);
}

void Expression::rename_expression(std::string renameValue)
{
    variable = renameValue;
    expressionNodePtr->element = renameValue;
}
