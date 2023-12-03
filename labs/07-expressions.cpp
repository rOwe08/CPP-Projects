// Name of the file: 07-expressions.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// Implementation an expression management application.

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <memory> 
#include <map>

#include "InputHandler.h"
#include "EvaluationManager.h"
#include "Expression.h"

int main()
{
    EvaluationManager evaluationManager;

    while (true)
    {
        try
        {
            std::vector<std::string> elements = create_array();

            if (elements[0] == "quit")
            {
                break;
            }
            evaluationManager.evaluate_expression(elements);
        }
        catch (std::runtime_error& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}

