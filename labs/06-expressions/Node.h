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

    Node(const std::string& elem) : element(elem) {}

    virtual ~Node() {}

    virtual void evaluate_node();
    virtual void print_node();
};

class BinaryNode : public Node
{
public:
    BinaryNode(const std::string& elem) : Node(elem) {}

    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    void evaluate_node() override;
    void print_node() override;

    void set_left(std::unique_ptr<Node> node);
    void set_right(std::unique_ptr<Node> node);


    Node* get_left() const;
    Node* get_right() const;
};

class NumNode : public Node
{
public:
    NumNode(const std::string& elem) : Node(elem) {}

    void evaluate_node() override;
    void print_node() override;
};

class Expression; 

class ExpressionNode : public Node
{
public:
    Expression* expression;
    ExpressionNode(const std::string& elem) : Node(elem) {}

    void evaluate_node() override;
    void print_node() override;
};

#endif
