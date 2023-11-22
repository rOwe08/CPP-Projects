#include "Node.h"
#include "Expression.h"
#include <iostream>
#include <memory>

void Node::evaluate_node() {};

void Node::print_node() {};


void BinaryNode::evaluate_node()
{
    long tempResult = 0;

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
    std::cout << element;
}

void NumNode::evaluate_node()
{
    std::string result = result;
    long number = std::atol(result.c_str());
}

void NumNode::print_node()
{
    std::cout << element;
}

void ExpressionNode::evaluate_node()
{   
    expression->evaluate();
}

void ExpressionNode::print_node()
{
    expression->print_result();
}