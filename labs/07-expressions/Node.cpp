#include "Node.h"
#include "Expression.h"
#include <iostream>
#include <memory>
#include "EvaluationManager.h"
#include "Exceptions.h"

void Node::evaluate_node() {};

void Node::print_node() {};

void Node::print_nodeElement()
{
    std::cout << element;
}

void BinaryNode::evaluate_node()
{
    left->evaluate_node();
    right->evaluate_node();
}

void AdditionNode::evaluate_node()
{
    left->evaluate_node();
    right->evaluate_node();
    result = left->result + right->result;
}

void MultiplicationNode::evaluate_node()
{
    //std::cout << left->element << ": " << left << std::endl;

    //std::cout << right->element << ": " << right << std::endl;

    std::string possibleNamespace = EvaluationManager::find_namespace_in_text(left->element);
    std::shared_ptr<Namespace> namespaceTemp = nullptr;

    if (possibleNamespace != "")
    {
        namespaceTemp = EvaluationManager::find_namespace(possibleNamespace);
    }

    if (namespaceTemp)
    {
        auto renameValueWithoutNamespace = EvaluationManager::getNameValue(left->element);

        auto expressionPtr = EvaluationManager::find_expression_or_create_in_namespace(renameValueWithoutNamespace, namespaceTemp);

        if (expressionPtr)
        {
            expressionPtr->expressionNodePtr->evaluate_node();

            left->result = expressionPtr->expressionNodePtr->result;
        }
        else
        {
            throw NonSpecificException();
        }
    }
    else
    {
        left->evaluate_node();
    }

    possibleNamespace = EvaluationManager::find_namespace_in_text(right->element);
    namespaceTemp = nullptr;

    if (possibleNamespace != "")
    {
        namespaceTemp = EvaluationManager::find_namespace(possibleNamespace);
    }

    if (namespaceTemp)
    {
        auto renameValueWithoutNamespace = EvaluationManager::getNameValue(right->element);

        auto expressionPtr = EvaluationManager::find_expression_or_create_in_namespace(renameValueWithoutNamespace, namespaceTemp);

        if (expressionPtr)
        {
            expressionPtr->expressionNodePtr->evaluate_node();

            right->result = expressionPtr->expressionNodePtr->result;
        }
        else
        {
            throw NonSpecificException();
        }
    }
    else
    {
        right->evaluate_node();
    }
    result = left->result * right->result;
}

void DivisionNode::evaluate_node()
{
    left->evaluate_node();
    right->evaluate_node();
    result = left->result / right->result;
}

void SubtractionNode::evaluate_node()
{
    left->evaluate_node();
    right->evaluate_node();
    result = left->result - right->result;
}

void UnaryNode::evaluate_node()
{
    
    child->evaluate_node();
    result = child->result;
}

void ConstNode::evaluate_node()
{
    result = std::stoi(element);
}

void BinaryNode::print_node()
{
    left->print_nodeElement();

    std::cout << " " << element << " ";

    right->print_nodeElement();

    //std::cout << left->element << ": " << left << std::endl;

    //std::cout << right->element << ": " << right << std::endl;
}

void UnaryNode::print_node()
{
    child->print_node();
}

void ConstNode::print_node()
{
    std::cout << element;
}

