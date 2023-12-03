#pragma once

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class CustomException : public std::runtime_error
{
public:
    explicit CustomException(const std::string& msg) : std::runtime_error(msg) {}
};

class NonSpecificException : public CustomException
{
public:
    explicit NonSpecificException() : CustomException("Operation failed.") {}
};

class NamespaceNotFoundException : public CustomException
{
public:
    explicit NamespaceNotFoundException(const std::string& ns)
        : CustomException("Namespace '" + ns + "' does not exist!"){}
};

#endif