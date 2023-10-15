// Name of the file: 02-string-update.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// Implementation a function that gets a string and changes each letter to upper case. Each number goes up by one. 
// The string is read character by character, so the number is always one character.

#include <iostream>
#include <string>

// Function name: getString
// Return value: string 
// 
// Description: 
// Makes from char value string value.

std::string getString(char x)
{
    std::string s(1, x);
    return s;
}

// Function name: magic
// Return value: string 
// Parameters: 
//      string result: variable for containing a result string
// 
// Description: 
// Changes each letter to upper case and increases each number by one

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

