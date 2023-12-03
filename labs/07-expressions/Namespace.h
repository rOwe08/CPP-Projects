#pragma once
#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <vector>
#include <string>
#include <memory>
#include "Expression.h"

class Namespace
{
public:
    std::string name;
    std::vector<std::shared_ptr<Expression>> expressionsVector;
};

#endif