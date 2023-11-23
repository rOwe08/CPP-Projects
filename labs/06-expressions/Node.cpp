#include "Node.h"
#include "Expression.h"
#include <iostream>
#include <memory>
#include "EvaluationManager.h"

void Node::evaluate_node() {};

void Node::print_node() {};


void BinaryNode::evaluate_node()
{
    left->evaluate_node();
    right->evaluate_node();

    if (element == "*")
    {
        result = left->result * right->result;
    }
    else if (element == "+")
    {
        result = left->result + right->result;
    }
    else if (element == "-")
    {
        result = left->result - right->result;
    }
    else if (element == "/")
    {
        result = left->result / right->result;
    }
}

void BinaryNode::set_left(std::unique_ptr<Node> node)
{
    left = std::move(node);
}

void BinaryNode::set_right(std::unique_ptr<Node> node)
{
    right = std::move(node);
}

Node* BinaryNode::get_left() const
{
    return left.get();
}

Node* BinaryNode::get_right() const
{
    return right.get();
}

void BinaryNode::print_node()
{
    left->print_node();
    std::cout << " " << element << " ";
    right->print_node();
}

void NumNode::evaluate_node()
{
    result = std::stoi(element);
}

void NumNode::print_node()
{
    std::cout << element;
}

void UnaryNode::evaluate_node()
{
    Expression* foundExp = EvaluationManager::find_expression(element);
    if (foundExp)
    {
        foundExp->evaluate();
        result = foundExp->result;
    }
    else
    {
        // Handle the case where no matching expression is found
    }
}

void UnaryNode::print_node()
{
    std::cout << element;
}