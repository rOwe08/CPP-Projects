#pragma once
#ifndef EVALUATION_MANAGER_H
#define EVALUATION_MANAGER_H

#include <string>
#include <memory>
#include <vector>
#include "Expression.h"

class EvaluationManager
{
public:
    static std::shared_ptr<std::vector<Expression>> expressionsPtr;

    void evaluate_expression(std::vector<std::string> elements);
    void set_expressionsPtr(std::shared_ptr<std::vector<Expression>> expressionsPtrTemp);

    static Expression* find_expression(const std::string& name);
};

#endif
