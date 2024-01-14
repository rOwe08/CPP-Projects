#include "Automaton.h"
#include <sstream>
#include <algorithm>
#include <iostream>

void Automaton::run()
{
    instructionCounter = 0;
    try
    {
        while (instructionCounter < instructions.size())
        {
            std::string currentInstruction = instructions[instructionCounter++];

            std::istringstream iss(currentInstruction);
            std::string command;
            iss >> command;

            //std::cout << "Executing command: " << command << std::endl;
            if (command == "const-int")
            {
                std::string value;
                iss >> value;
                //std::cout << "Const-int value: " << value << std::endl;
                executeConstInt(value);
            }
            else if (command == "const-string")
            {
                std::string value;
                iss >> value;
                executeConstString(value);
            }
            else if (command == "pop")
            {
                executePop();
            }
            else if (command == "stoi")
            {
                executeStoi();
            }
            else if (command == "add")
            {
                executeAdd();
            }
            else if (command == "store")
            {
                std::string variableName;
                iss >> variableName;
                executeStore(variableName);
            }
            else if (command == "load")
            {
                std::string variableName;
                iss >> variableName;
                executeLoad(variableName);
            }
            else if (command == "read")
            {
                executeRead();
            }
            else if (command == "print")
            {
                executePrint();
            }
            else if (command == "section")
            {
                std::string label;
                iss >> label;
                executeSection(label);
            }
            else if (command == "goto")
            {
                std::string label;
                iss >> label;
                executeGoto(label);
            }
            else if (command == "jump")
            {
                executeJump();
            }
        }
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
}

bool Automaton::loadInstructions(std::istream& input)
{
    std::string line;
    while (std::getline(input, line))
    {
        auto commentPos = line.find('#');
        if (commentPos != std::string::npos)
        {
            line = line.substr(0, commentPos);
        }

        if (line.empty())
        {
            continue;
        }

        if (!isValidInstruction(line))
        {
            return false;
        }

        instructions.push_back(line);
    }
    return true;
}

bool Automaton::isValidInstruction(const std::string& line)
{
    return true;
}

void Automaton::executeConstInt(const std::string& value)
{
    //std::cout << "Pushing to stack: " << value << std::endl;
    stack.push(value);
    //std::cout << "Stack size after pushing: " << stack.size() << std::endl;
}

void Automaton::executeConstString(const std::string& value)
{
    stack.push(value);
}

void Automaton::executePop()
{
    if (stack.empty())
    {
        throw std::runtime_error("Stack underflow");
    }
    stack.pop();
}

void Automaton::executeStoi()
{
    if (stack.empty())
    {
        throw std::runtime_error("Stack underflow");
    }
    std::string top = stack.top();
    stack.pop();
    stack.push(std::to_string(std::stoi(top)));
}

void Automaton::executeAdd()
{
    //std::cout << "Stack size before add: " << stack.size() << std::endl;
    if (stack.size() < 2)
    {
        throw std::runtime_error("Stack underflow");
    }
    std::string a = stack.top(); stack.pop();
    std::string b = stack.top(); stack.pop();

    try
    {
        int int_a = std::stoi(a);
        int int_b = std::stoi(b);
        int result = int_a + int_b;
        stack.push(std::to_string(result));
    }
    catch (const std::invalid_argument&)
    {

        stack.push(a + b);
    }
    //std::cout << "Stack size after add: " << stack.size() << std::endl;
}

void Automaton::executeStore(const std::string& variableName)
{
    if (stack.empty())
    {
        throw std::runtime_error("Stack underflow");
    }
    variables[variableName] = stack.top();
    stack.pop();
}

void Automaton::executeLoad(const std::string& variableName)
{
    auto it = variables.find(variableName);
    if (it == variables.end())
    {
        throw std::runtime_error("Variable not found: " + variableName);
    }
    stack.push(it->second);
}

void Automaton::executeRead()
{
    std::string inputLine;
    std::getline(std::cin, inputLine);
    stack.push(inputLine);
}

void Automaton::executePrint()
{
    if (stack.empty())
    {
        throw std::runtime_error("Stack underflow");
    }
    std::cout << stack.top() << std::endl;
    stack.pop();
}

void Automaton::executeSection(const std::string& label)
{
    labels[label] = instructionCounter - 1;
    std::cout << "Section registered: " << label << " at line " << instructionCounter - 1 << std::endl;
}

void Automaton::executeGoto(const std::string& label)
{
    auto it = labels.find(label);
    if (it == labels.end())
    {
        std::cerr << "Label not found: " << label << std::endl;
        throw std::runtime_error("Label not found: " + label);
    }
    instructionCounter = it->second - 1;
}


void Automaton::executeJump()
{
    if (stack.empty())
    {
        throw std::runtime_error("Stack underflow");
    }
    int line = std::stoi(stack.top()); stack.pop();
    if (line < 0 || line >= instructions.size())
    {
        throw std::runtime_error("Invalid jump destination");
    }
    instructionCounter = line;
}
