#include <iostream>

std::string revert(std::string inputString) 
{
    std::string result;

    for (int i = inputString.length() - 1; i > -1; i--)
    {
        result.push_back(inputString[i]);
    }
    return result;
}

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
