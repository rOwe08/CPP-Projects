#include <iostream>
#include <fstream>
#include <string>
#include "Automaton.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
        return 1;
    }

    std::string source_file = argv[1];
    std::ifstream file(source_file);
    if (!file)
    {
        std::cerr << "Error: Cannot open file " << source_file << std::endl;
        return 1;
    }

    Automaton automaton;
    if (!automaton.loadInstructions(file))
    {
        std::cerr << "Invalid source code." << std::endl;
        return 1;
    }

    automaton.run();

    return 0;
}
