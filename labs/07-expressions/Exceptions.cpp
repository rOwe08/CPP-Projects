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
