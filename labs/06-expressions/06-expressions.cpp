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
        std::vector<std::string> elements = create_array();

        if (elements.empty() || elements[0] == "quit")
        {
            break;
        }

        evaluationManager.evaluate_expression(elements);
    }

    return 0;
}
