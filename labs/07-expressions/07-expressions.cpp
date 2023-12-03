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
#include "Exceptions.h"

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
            else if (elements.size() < 2)
            {
                throw NonSpecificException();
            }

            evaluationManager.evaluate_expression(elements);
        }
        catch (const CustomException& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}

