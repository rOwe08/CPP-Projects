// Name of the file: 09-aggregator.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// Designing and implementing a class template that adds up all passed values.

#include <iostream>
#include <string>

template <typename T>
class Aggregator
{
private:
    T result;

public:
    Aggregator() : result(T()) {}

    Aggregator& operator+=(const T& other)
    {
        result += other;
        return *this;
    }

    T getValue() const
    {
        return result;
    }
};

int main()
{
    Aggregator<int> numbers;
    numbers += 1;
    numbers += 2;
    std::cout << numbers.getValue() << std::endl; // 3

    Aggregator<std::string> strings;
    strings += "a";
    strings += "b";
    std::cout << strings.getValue() << std::endl; // ab

    return 0;
}
