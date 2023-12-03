#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Node.h"
#include "Expression.h"
#include "EvaluationManager.h"

void Expression::evaluate()
{
    std::string possibleNamespace = EvaluationManager::find_namespace_in_text(expressionNodePtr->element);
    std::shared_ptr<Namespace> namespaceTemp = nullptr;

    if (possibleNamespace != "")
    {
        namespaceTemp = EvaluationManager::find_namespace(possibleNamespace);
    }

    if (namespaceTemp)
    {
        auto renameValueWithoutNamespace = EvaluationManager::getNameValue(expressionNodePtr->element);

        auto expressionPtr = EvaluationManager::find_expression_or_create_in_namespace(renameValueWithoutNamespace, namespaceTemp);
        
        if (expressionPtr)
        {
            expressionPtr->expressionNodePtr->evaluate_node();

            result = expressionPtr->expressionNodePtr->result;
        }
        else
        {
            std::cout << "NO EXPRESSION FOUND" << std::endl;
        }
    }
    else
    {
        expressionNodePtr->evaluate_node();
        result = expressionNodePtr->result;
    }

}

void Expression::print_result()
{
    std::cout << std::to_string(result) << std::endl;
}

void Expression::print_expression()
{
    expressionNodePtr->print_node();
}

void Expression::set_expression(std::vector<std::string>& elements, std::shared_ptr<Namespace> namespacePtrTemp)
{
    std::string name = elements[1];
    std::string symbol = elements[3];
    std::shared_ptr<UnaryNode> root;       
    std::shared_ptr<Expression> expressionPtrRoot;
    std::shared_ptr<Namespace> namespaceCurrentPtr;

    if (namespacePtrTemp)
    {
        namespaceCurrentPtr = namespacePtrTemp;
    }
    else
    {
        namespaceCurrentPtr = EvaluationManager::currentNamespacePtr;
    }

    expressionPtrRoot = EvaluationManager::find_expression(name, namespaceCurrentPtr);

    if (!expressionPtrRoot)
    {
        root = std::make_shared<UnaryNode>(name);      
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
            child->left = std::make_shared<ConstNode>(std::to_string(value));
        }
        catch (...)
        {
            std::shared_ptr<Expression> expressionPtr = EvaluationManager::find_ptr_for_set(elements[4]);
            child->left = expressionPtr->expressionNodePtr;
        }

        try
        {
            int value = std::stoi(elements[5]);
            child->right = std::make_shared<ConstNode>(std::to_string(value));
        }
        catch (...)
        {
            std::shared_ptr<Expression> expressionPtr = EvaluationManager::find_ptr_for_set(elements[5]);
            child->right = expressionPtr->expressionNodePtr;
        }

        root->child = child;

        expressionNodePtr = root;

        //std::cout << child->left->element << ": " << child->left << std::endl;
        //std::cout << child->right->element << ": " << child->right << std::endl;
    }
    else
    {
        std::shared_ptr<UnaryNode> child;

        try
        {
            int value = std::stoi(symbol);
            child = std::make_shared<ConstNode>(std::to_string(value));
        }
        catch (...)
        {
            child = std::make_shared<UnaryNode>(symbol);
        }

        root->child = child;

        expressionNodePtr = root;
        //std::cout << root->element << ": " << root << std::endl;
    }

}

void Expression::copy_expression(std::string& targetName)
{
    auto copiedExpr = std::make_shared<Expression>();
    copiedExpr->variable = targetName;

    copiedExpr->expressionNodePtr = expressionNodePtr;

    EvaluationManager::currentNamespacePtr->expressionsVector.push_back(copiedExpr);
}

void Expression::rename_expression(std::string renameValue)
{
    variable = renameValue;
    expressionNodePtr->element = renameValue;
}
