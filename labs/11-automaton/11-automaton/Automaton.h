#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <vector>
#include <string>
#include <map>
#include <stack>

class Automaton
{
public:
    bool loadInstructions(std::istream& input);
    void run();

private:
    bool isValidInstruction(const std::string& line);

    void executeConstInt(const std::string& value);
    void executeConstString(const std::string& value);
    void executePop();
    void executeStoi();
    void executeAdd();

    void executeStore(const std::string& variableName);
    void executeLoad(const std::string& variableName);

    void executeRead();
    void executePrint();

    void executeSection(const std::string& label);
    void executeGoto(const std::string& label);
    void executeJump();

    std::vector<std::string> instructions;
    std::stack<std::string> stack;
    std::map<std::string, std::string> variables;
    int instructionCounter;

    std::map<std::string, size_t> labels;
};

#endif // AUTOMATON_H
