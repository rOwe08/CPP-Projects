#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "InputHandler.h"

std::vector<std::string> create_array()
{
    std::string line;
    getline(std::cin, line);

    std::istringstream iss(line);
    std::vector<std::string> cells;
    std::string cell;

    while (getline(iss, cell, ' '))
    {
        if (!cell.empty())
        {
            cells.push_back(cell);
        }
    }

    return cells;
}