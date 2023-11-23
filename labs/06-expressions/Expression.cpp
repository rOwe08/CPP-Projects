#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Node.h"
#include "Expression.h"

void Expression::evaluate()
{
    expressionNode->evaluate_node();
    result = expressionNode->result;
}

void Expression::print_result()
{
    std::cout << std::to_string(result) << std::endl;
}

void Expression::print_expression()
{
    expressionNode->print_node();
}

void Expression::set_expression(std::vector<std::string>& elements)
{
    if (elements.size() > 4)
    {
        operationSymbol = elements[3];
        auto root = std::make_unique<BinaryNode>(operationSymbol);

        try
        {
            std::stoi(elements[4]);
            root->set_left(std::make_unique<NumNode>(elements[4]));
        }
        catch (...)
        {
            root->set_left(std::make_unique<UnaryNode>(elements[4]));
        }
        
        try
        {
            std::stoi(elements[5]);
            root->set_right(std::make_unique<NumNode>(elements[5]));
        }
        catch (...)
        {
            root->set_right(std::make_unique<UnaryNode>(elements[5]));
        }
        

        expressionNode = std::move(root);
    }
    else
    {
        auto root = std::make_unique<NumNode>(elements[3]);
        expressionNode = std::move(root);
    }
}

void Expression::unset_expression()
{
    expressionNode = nullptr;
    result = NULL;
    //operationSymbol = NULL;
}

void Expression::copy_expression()
{
    std::cout << std::to_string(result) << std::endl;
}

void Expression::rename_expression(std::string renameValue)
{
    variable = renameValue;
}
