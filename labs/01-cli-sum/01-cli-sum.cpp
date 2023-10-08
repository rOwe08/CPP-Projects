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
