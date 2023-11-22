#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <memory> 

#include "InputHandler.h"
#include "EvaluationManager.h"
#include "Expression.h"

int main()
{
    std::vector<Expression> expressions;

    while (true)
    {
        std::vector<std::string> elements = create_array();

        if (elements.empty() || elements[0] == "quit")
        {
            break;
        }

        evaluate_expression(elements, expressions);
    }

    return 0;
}
