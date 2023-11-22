#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Node.h"
#include "Expression.h"

std::pair<std::unique_ptr<Node>, int> Expression::insert_node(const std::vector<std::string>& elements, int index)
{
    auto root = create_node(elements[index]);

    //if (auto unaryRoot = dynamic_cast<UnaryNode*>(root.get()))
    //{
    //    if (index < elements.size() - 1)
    //    {
    //        auto result = insert_node(elements, index + 1);
    //        unaryRoot->center = std::move(result.first);
    //        index = result.second;
    //    }
    //}
    //else if (auto binaryRoot = dynamic_cast<BinaryNode*>(root.get()))
    //{
    //    if (index < elements.size() - 1)
    //    {
    //        auto result = insert_node(elements, index + 1);
    //        binaryRoot->left = std::move(result.first);
    //        index = result.second;
    //    }
    //    if (index < elements.size() - 1)
    //    {
    //        auto result = insert_node(elements, index + 1);
    //        binaryRoot->right = std::move(result.first);
    //        index = result.second;
    //    }
    //}

    return { std::move(root), index };
}

std::unique_ptr<Node> Expression::create_node(const std::string& element)
{
    try
    {
        std::stoi(element);
        return std::make_unique<NumNode>(element);
    }
    catch (...)
    {
        return std::make_unique<BinaryNode>(element);
    }
}

void Expression::evaluate()
{
    std::cout << std::to_string(result) << std::endl;
}

void Expression::print_result()
{
    std::cout << std::to_string(result) << std::endl;
}

void Expression::print_expression()
{
    expressionNode->print_node();
}

void Expression::set_expression()
{
    std::cout << std::to_string(result) << std::endl;
}

void Expression::unset_expression()
{
    std::cout << std::to_string(result) << std::endl;
}

void Expression::copy_expression()
{
    std::cout << std::to_string(result) << std::endl;
}

void Expression::rename_expression(std::string renameValue)
{
    variable = renameValue;
}

std::unique_ptr<Node> Expression::create_tree(const std::vector<std::string>& elements)
{
    auto result = insert_node(elements, 0);
    if (result.second == elements.size())
    {
        return std::move(result.first);
    }
    return nullptr;
}

std::string Expression::evaluate_tree(const Node* node)
{
    //if (dynamic_cast<const BinaryNode*>(node) || dynamic_cast<const UnaryNode*>(node))
    //{
    //    return node->evaluate_node();
    //}
    return "Invalid Node Type";
}