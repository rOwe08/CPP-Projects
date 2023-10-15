// Name of the file: 01-cli-sum.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// Load the arguments from the command line and print their sum. Arguments are loaded as numbers.

#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[]) {
    int sum = 0;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--range" && i + 2 < argc) {
            int from = std::stoi(argv[i + 1]);
            int to = std::stoi(argv[i + 2]);

            for(int j = from; j < to + 1; j++){
                sum += j;
            }
            i += 2;
        } else {
            int number = std::stoi(argv[i]);
            sum += number;
        }
    }

    std::cout << sum << std::endl;
    return 0;
}
