#pragma once
#ifndef NODE_H
#define NODE_H

#include <string>
#include <memory>
#include "Expression.h"

class Node
{
public:
    std::string element;
    int result;

    Node(const std::string& elem) : element(elem), result(0) {}

    virtual ~Node() {}

    virtual void evaluate_node() = 0;
    virtual void print_node();
    virtual void print_nodeElement();
};

class BinaryNode : public Node
{
public:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    BinaryNode(const std::string& elem) : Node(elem) {}

    void evaluate_node() override;
    void print_node() override;
};

class UnaryNode : public Node
{
public:
    std::shared_ptr<Node> child;

    UnaryNode(const std::string& elem) : Node(elem) {}

    void evaluate_node() override;
    void print_node() override;
};

class AdditionNode : public BinaryNode
{
public:
    AdditionNode(const std::string& elem) : BinaryNode(elem) {}
    void evaluate_node() override;
};

class SubtractionNode : public BinaryNode
{
public:
    SubtractionNode(const std::string& elem) : BinaryNode(elem) {}
    void evaluate_node() override;
};

class DivisionNode : public BinaryNode
{
public:
    DivisionNode(const std::string& elem) : BinaryNode(elem) {}
    void evaluate_node() override;
};

class MultiplicationNode : public BinaryNode
{
public:
    MultiplicationNode(const std::string& elem) : BinaryNode(elem) {}
    void evaluate_node() override;
};

class ConstNode : public UnaryNode
{
public:
    ConstNode(const std::string& elem) : UnaryNode(elem) {}
    void print_node() override;
    void evaluate_node() override;
};

#endif
