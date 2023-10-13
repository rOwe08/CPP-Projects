#include <iostream>
#include <string>

std::string getString(char x)
{
    std::string s(1, x);
    return s;
}

std::string magic(std::string inputString)
{
    std::string result;

    for (int i = 0; i < inputString.length(); i++)
    {
        if (std::isdigit(inputString[i]))
        {
            int num = std::stoi(getString(inputString[i])) + 1;
            std::string element = std::to_string(num);
            result += element;
        }
        else
        {
            char c = std::toupper(inputString[i]);
            result += c;
        }
    }
    return result;
}

int main()
{
    std::string original = "m3ssage92";
    std::string modified = magic(original);

    std::cout << "Expected value 'M3SSAGE103'" << std::endl;  //Expected value should be 'M4SSAGE103'
    std::cout << "Actual value   '" << modified << "'" << std::endl;
}

