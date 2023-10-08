#include <iostream>
#include <vector>
#include <string>

using namespace std;                                    // Adding this line to avoid writing std:: every time :(

void printSubset(const vector<string>& currentSubset) {
    for (int i = 0; i < currentSubset.size(); i++) {
        cout << currentSubset[i];
        if (i != currentSubset.size() - 1) {            // Avoiding printing a space on the end of the result
            cout << " ";
        }
    }
    cout << endl;
}

void generateSubsets(const vector<string>& tokens, vector<string>& currentSubset, int index) {
    if (index == tokens.size()) {                       // Printing the result
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
    vector<string> tokens;

    for (int i = 1; i < argc; i++) {                    // Moving all tokens from the command line to the container
        tokens.push_back(argv[i]);
    }

    vector<string> currentSubset;
    generateSubsets(tokens, currentSubset, 0);          // Processing all tokens

    return 0;
}
