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
    std::vector<std::string> elements = create_array();
    std::vector<Expression> expressions;

    if (!elements.empty())
    {
        std::string command = elements[0];
        evaluate_expression(elements, expressions);
    }

    return 0;
}
