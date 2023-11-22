#pragma once
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Node.h"
#include <vector>
#include <string>
#include <memory>

class Node;

class Expression
{
public:
    int result;
    std::vector<std::string> operationSymbol;
    std::string variable;
    Node* expressionNode;

    std::unique_ptr<Node> create_node(const std::string& element);
    std::pair<std::unique_ptr<Node>, int> insert_node(const std::vector<std::string>& elements, int index);
    std::unique_ptr<Node> create_tree(const std::vector<std::string>& elements);
    std::string evaluate_tree(const Node* node);

    void evaluate();
    void print_result();
    void print_expression();
    void set_expression();
    void unset_expression();
    void copy_expression();
    void rename_expression(std::string renameValue);
};

#endif