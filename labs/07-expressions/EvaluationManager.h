#pragma once
#ifndef EVALUATION_MANAGER_H
#define EVALUATION_MANAGER_H

#include <string>
#include <memory>
#include <vector>
#include <map>
#include "Expression.h"
#include "Namespace.h"

class EvaluationManager
{
public:
    EvaluationManager()
    {
        auto defaultNamespace = std::make_shared<Namespace>();
        defaultNamespace->name = "default";
        namespacesPtrVector.push_back(defaultNamespace);
        currentNamespacePtr = defaultNamespace;
    }

    static std::vector<std::shared_ptr<Namespace>> namespacesPtrVector;
    static std::shared_ptr<Namespace> currentNamespacePtr;

    void evaluate_expression(std::vector<std::string> elements);
    static void printExpressionPointers();

    static std::shared_ptr<Namespace> find_namespace(const std::string& name);
    void create_namespace(std::string& name);
    void use_namespace(std::string& name);
    void list_namespaces();

    static std::shared_ptr<Expression> find_expression_in_namespace(const std::string& name, std::shared_ptr<Namespace> namespacePtr);
    static std::string find_namespace_in_text(std::string name);
    static std::shared_ptr<Expression> find_expression(const std::string& name, std::shared_ptr<Namespace> namespacePtr);
    static std::string getNameValue(const std::string& fullName);
};

#endif
