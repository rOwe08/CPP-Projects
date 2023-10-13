#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int detectedMinus = 1;

std::string getString(char x)
{
    std::string s(1, x);
    return s;
}

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

