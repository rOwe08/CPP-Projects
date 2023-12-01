// Name of the file: 07-exceptions.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// Creating an application that reads integers with standard input and treats STD::stoi function failure.

#include <iostream>
#include <string>
#include <stdexcept>

class NumberTooLargeException : public std::exception
{
public:
    NumberTooLargeException() = default;
    const char* what() const noexcept override
    {
        return "Number is too large!";
    }
};

int main()
{
    std::string input;
    const int MAX_NUMBER = 100;             // Change the max value, if you need it
    std::string messageInput = "Enter a number: ";

    std::cout << messageInput;

    while (std::getline(std::cin, input))
    {
        try
        {
            int number = std::stoi(input);

            if (number > MAX_NUMBER)
            {
                throw NumberTooLargeException();
            }

            std::cout << "Everything is fine!:)" << std::endl;
        }
        catch (const NumberTooLargeException& e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "Invalid argument." << std::endl;
        }
        catch (const std::out_of_range& e)
        {
            std::cout << "Out of range." << std::endl;
        }

        std::cout << messageInput;
    }

    return 0;
}
