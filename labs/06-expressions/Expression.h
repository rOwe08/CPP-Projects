#pragma once
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Node.h"
#include <vector>
#include <string>
#include <memory>

class UnaryNode;

class Expression
{
public:
    int result = 0;
    std::string operationSymbol = "";
    std::string variable = "";
    std::shared_ptr<UnaryNode> expressionNodePtr = nullptr;

    void evaluate();
    void print_result();
    void print_expression();
    void set_expression(std::vector<std::string>& elements);
    void copy_expression(std::string& targetName);
    void rename_expression(std::string renameValue);
};

#endif