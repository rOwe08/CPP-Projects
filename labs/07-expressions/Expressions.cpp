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
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        try
        {
            int value = std::stoi(elements[4]);
            child->left = std::make_shared<ConstNode>(elements[4]);
        }
        catch (...)
        {
            std::shared_ptr<Expression> expressionPtr = nullptr;

            std::string possibleNamespace = EvaluationManager::find_namespace_in_text(elements[4]);

            auto namespaceTemp = EvaluationManager::find_namespace(possibleNamespace);                 ////// if is null!!!!!!!!!!!???????????

            if (namespaceTemp)
            {
                expressionPtr = EvaluationManager::find_expression_in_namespace(elements[4], namespaceTemp);
            }
            else
            {
                expressionPtr = EvaluationManager::find_expression_in_namespace(elements[4], EvaluationManager::currentNamespacePtr);
            }

            if (!expressionPtr)
            {
                expressionPtr = std::make_shared<Expression>();
                expressionPtr->variable = elements[4];

                expressionPtr->expressionNodePtr = std::make_shared<UnaryNode>(elements[4]);
                EvaluationManager::currentNamespacePtr->expressionsVector.push_back(expressionPtr);
            }

            child->left = expressionPtr->expressionNodePtr;
        }

        try
        {
            int value = std::stoi(elements[5]);
            child->right = std::make_shared<ConstNode>(elements[5]);
        }
        catch (...)
        {

            std::shared_ptr<Expression> expressionPtr = nullptr;

            std::string possibleNamespace = EvaluationManager::find_namespace_in_text(elements[5]);

            auto namespaceTemp = EvaluationManager::find_namespace(possibleNamespace);                 ////// if is null!!!!!!!!!!!???????????

            if (namespaceTemp)
            {
                expressionPtr = EvaluationManager::find_expression_in_namespace(elements[5], namespaceTemp);
            }
            else
            {
                expressionPtr = EvaluationManager::find_expression_in_namespace(elements[5], EvaluationManager::currentNamespacePtr);
            }

            if (!expressionPtr)
            {
                expressionPtr = std::make_shared<Expression>();
                expressionPtr->variable = elements[5];

                expressionPtr->expressionNodePtr = std::make_shared<UnaryNode>(elements[5]);
                EvaluationManager::currentNamespacePtr->expressionsVector.push_back(expressionPtr);
            }

            child->right = expressionPtr->expressionNodePtr;
        }

        root->child = child;

        expressionNodePtr = root;

        std::cout << child->left->element << ": " << child->left << std::endl;

        std::cout << child->right->element << ": " << child->right << std::endl;
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
        std::cout << root->element << ": " << root << std::endl;
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
    std::shared_ptr<Expression> expressionPtr = nullptr;

    std::string possibleNamespace = EvaluationManager::find_namespace_in_text(renameValue);

    auto namespaceTemp = EvaluationManager::find_namespace(possibleNamespace);                 ////// if is null!!!!!!!!!!!???????????

    std::cout << "Before: " << expressionNodePtr->element << ": " << expressionNodePtr << std::endl;

    if (namespaceTemp)
    {
        auto renameValueWithoutNamespace = EvaluationManager::getNameValue(renameValue);

        expressionPtr = EvaluationManager::find_expression_in_namespace(renameValueWithoutNamespace, namespaceTemp);
        expressionNodePtr = expressionPtr->expressionNodePtr;
    }

    variable = renameValue;
    expressionNodePtr->element = renameValue;

    std::cout << "After: " << expressionNodePtr->element << ": " << expressionNodePtr << std::endl;
}
