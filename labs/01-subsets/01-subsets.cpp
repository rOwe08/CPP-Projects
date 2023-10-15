// Name of the file: 01-subsets.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// The input of the program are arguments from the command line tokens separated by a space. No token is repeated at the input. 
// The output of the program lists all subsets of tokens without repetition and preserving the order of tokens. The order of the output does not matter.

#include <iostream>
#include <vector>
#include <string>

// Function name: printSubset
// Return value: void 
// 
// Description: 
// Prints all elements in a subset

void printSubset(const std::vector<std::string>& currentSubset) {
    for (int i = 0; i < currentSubset.size(); i++) {
        cout << currentSubset[i];
        if (i != currentSubset.size() - 1) {            // Avoiding printing a space on the end of the result
            cout << " ";
        }
    }
    cout << endl;
}

// Function name: generateSubsets
// Return value: void 
// 
// Description: 
// Recursive function for generating subsets

void generateSubsets(const std::vector<string>& tokens, std::vector<std::string>& currentSubset, int index) {
    if (index == tokens.size()) {                  
        if (!currentSubset.empty()) {
            printSubset(currentSubset);
        }
        return;
    }

    generateSubsets(tokens, currentSubset, index + 1);  // Excluding the current token

    currentSubset.push_back(tokens[index]);
    generateSubsets(tokens, currentSubset, index + 1);  // Including the current token
    currentSubset.pop_back();                           // Removing the current token for backtracking
}

int main(int argc, char* argv[]) {
    std::vector<std::string> tokens;

    for (int i = 1; i < argc; i++) {                    // Moving all tokens from the command line to the container
        tokens.push_back(argv[i]);
    }

    std::vector<std::string> currentSubset;
    generateSubsets(tokens, currentSubset, 0);          // Processing all tokens

    return 0;
}
