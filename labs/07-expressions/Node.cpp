#include "Node.h"
#include "Expression.h"
#include <iostream>
#include <memory>
#include "EvaluationManager.h"

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
    std::cout << left->element << ": " << left << std::endl;

    std::cout << right->element << ": " << right << std::endl;


    left->evaluate_node();
    right->evaluate_node();

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

    std::cout << left->element << ": " << left << std::endl;

    std::cout << right->element << ": " << right << std::endl;
}

void UnaryNode::print_node()
{
    child->print_node();
}

void ConstNode::print_node()
{
    std::cout << element;
}

