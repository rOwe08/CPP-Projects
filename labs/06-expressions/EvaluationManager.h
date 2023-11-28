#pragma once
#ifndef EVALUATION_MANAGER_H
#define EVALUATION_MANAGER_H

#include <string>
#include <memory>
#include <vector>
#include <map>
#include "Expression.h"

class EvaluationManager
{
public:
    static std::vector<std::shared_ptr<Expression>> expressionsVector;

    void evaluate_expression(std::vector<std::string> elements);
    void set_expressionsPtr(std::shared_ptr<std::vector<Expression>> expressionsPtrTemp);
    static void printExpressionPointers();

    static std::shared_ptr<Expression> find_expression(const std::string& name);
};

#endif
