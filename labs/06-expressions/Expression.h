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
    std::string operationSymbol;
    std::string variable;
    std::unique_ptr<Node> expressionNode;

    void evaluate();
    void print_result();
    void print_expression();
    void set_expression(const std::vector<std::string>& elements);
    void unset_expression();
    void copy_expression();
    void rename_expression(std::string renameValue);
};

#endif