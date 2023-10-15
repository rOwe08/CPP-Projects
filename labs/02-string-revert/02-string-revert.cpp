// Name of the file: 02-string-revert.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// Implementation the revert and revertInPlace functions for the code in main() function.

#include <iostream>

// Function name: revert
// Return value: string 
// Parameters: 
//      string result: variable for containing a result string
// 
// Description: 
// Reverts a given string not in place

std::string revert(std::string inputString) 
{
    std::string result;

    for (int i = inputString.length() - 1; i > -1; i--)
    {
        result.push_back(inputString[i]);
    }
    return result;
}

// Function name: revertInPlace
// Return value: void 
// Parameters: 
//      string result: variable for containing a result string
//      int i,j: variables for index containing
// 
// Description: 
// Reverts a given string in place

void revertInPlace(std::string& inputString)
{
    char tempSymbol;
    int i = 0;
    int j = inputString.length() - 1;

    while (i < j)
    {
        tempSymbol = inputString[i];
        inputString[i] = inputString[j];
        inputString[j] = tempSymbol;
        i++;
        j--;
    }
}

int main()
{
    std::string original = "123456789";
    auto reverted = revert(original);
    auto reverted_twice = revert(reverted);

    revertInPlace(original);

    std::cout << "Reverted original (987654321): " << original << std::endl
        << "Reverted (987654321): " << reverted << std::endl
        << "Reverted twice (123456789): " << reverted_twice << std::endl;
}
