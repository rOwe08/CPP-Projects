#pragma once
#ifndef EVALUATION_MANAGER_H
#define EVALUATION_MANAGER_H

#include <string>
#include <memory>
#include "Expression.h"

void evaluate_expression(std::vector<std::string> elements, std::vector<Expression>& expressions);

#endif
