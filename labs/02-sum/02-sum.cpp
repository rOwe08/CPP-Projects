// Name of the file: 02-sum.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// Input: two arguments from the command line. (1-name of the input file, 2-name of the output file). 
// If the first argument is '-' the program reads from standard input. If the second argument is '-', the program writes to the standard output.
// The Program processes input line by line. On each line, the program adds up the value of the numbers and evaluates the expressions '+' and '-'.
// Other characters are ignored by the program. The resulting value is then written to the output line.
// The expression is a separation from both sides by a space, and does not contain a space itself and evaluated in the reading order.
// If the input line, or does not contain a number, prints the program 0.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int detectedMinus = 1;

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

// Function name: getSum
// Return value: int 
// Parameters: 
//      int sum: variable for containing a sum of numbers
// 
// Description: 
// Counts and returns a sum of numbers in given string

int getSum(std::string input)
{
    int sum = 0;

    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == '-')
        {
            detectedMinus *= -1;
        }
        else if (std::isdigit(input[i]))
        {
            sum += std::stoi(getString(input[i])) * detectedMinus;
            detectedMinus = 1;
        }
    }

    return sum;
}

// Function name: processSecondParameter
// Return value: void
// 
// Description: 
// Decides where the answer will be recorded.

void processSecondParameter(int sum, std::string secondParameter)
{
    if (secondParameter == "-")  // Standard output
    {
        std::cout << sum << std::endl;
    }
    else  // Output to file (append mode)
    {
        std::ofstream outputFile(secondParameter, std::ios::app);
        if (outputFile.is_open())
        {
            outputFile << sum << '\n';
            outputFile.close();
        }
    }
}

int main(int argc, char* argv[])
{
    std::string firstParameter = argv[1];
    std::string secondParameter = argv[2];

    if (firstParameter == "-")  // Standard input
    {
        for (;;)
        {
            std::string input;
            std::getline(std::cin, input);
            int sum = getSum(input);
            processSecondParameter(sum, secondParameter);
        }
    }
    else  // Input from file
    {
        std::vector<std::string> inputArray;

        std::ifstream inputFile(firstParameter);
        if (inputFile.is_open())
        {
            std::string line;
            while (getline(inputFile, line))
            {
                inputArray.push_back(line);
            }
            inputFile.close();
        }

        for (std::string inputLine : inputArray)
        {
            int sum = getSum(inputLine);
            processSecondParameter(sum, secondParameter);
        }
    }

    return 0;
}

