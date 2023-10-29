// Name of the file: 04-dictionary.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// Implementation of a full version of a translation dictionary

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// Word class to store the word and its translations
class Word
{
public:
    std::string name;
    std::vector<std::string> translations;

    // Sorts the translations of a word by their length in ascending order.
    // This uses the std::sort algorithm from the <algorithm> header and a custom
    // lambda function to define the sorting criteria.
    void sortTranslationsByLength()
    {
        std::sort(translations.begin(), translations.end(), [](const std::string& a, const std::string& b)
            {
                return a.length() < b.length();
            });
    }

    // Function to print the translations of a word
    void printTranslations()
    {
        std::cout << "Translations: ";
        for (const auto& translation : translations)
        {
            std::cout << translation << ' ';
        }
        std::cout << std::endl;
    }
};


class Dictionary
{
public:
    std::vector<Word> words;

    // Function to find a word in the dictionary by its name
    // and return a pointer to the Word object. If the word is not found, 
    // it returns nullptr.
    Word* findWord(const std::string& word)
    {
        for (auto& entry : words)
        {
            if (entry.name == word)
            {
                return &entry;
            }
        }
        return nullptr;
    }

    // Function to add a word to the dictionary
    void addWord(const std::string& word)
    {
        Word newWord;
        newWord.name = word;
        words.push_back(newWord);
    }

    // Function to delete a word from the dictionary
    void deleteWord(Word* wordObject)
    {
        auto position = wordObject - &words[0];
        if (position >= 0 && position < words.size())
        {
            words.erase(words.begin() + position);
        }
    }

    // Function to delete specific translations of a word from the dictionary
    void deleteWordTranslations(Word* wordObject, const std::vector<std::string>& translationsToDelete)
    {
        for (const auto& translation : translationsToDelete)
        {
            wordObject->translations.erase(std::remove(wordObject->translations.begin(), wordObject->translations.end(), translation), wordObject->translations.end());
        }
    }

    // Function to find all words that start with a given prefix
    // and returns a vector of pointers to these Word objects.
    std::vector<Word*> findWordsWithPrefix(const std::string& prefix)
    {
        std::vector<Word*> results;
        for (auto& entry : words)
        {
            if (entry.name.substr(0, prefix.size()) == prefix)
            {
                results.push_back(&entry);
            }
        }
        return results;
    }
};

class UI
{
    // Function to display the available commands to the user and get
    // the user's input command.
    public:
        static std::string getInputCommand()
        {
            printUIMenu();
            std::string input;
            std::getline(std::cin, input);
            std::cout << std::endl;
            return input;
        }

        // Function to print the menu options available to the user.
        static void printUIMenu()
        {
            std::cout << std::endl;
            std::cout << "--- Available Commands ---" << std::endl;
            std::cout << "add [word] [translations...] : Adds a word and its translations." << std::endl;
            std::cout << "del [word] [translations...] : Deletes a word or its specific translations." << std::endl;
            std::cout << "find [word]                  : Finds a word and prints its translations." << std::endl;
            std::cout << "prefix [prefix]              : Finds words that start with the given prefix and prints their translations." << std::endl;
            std::cout << "quit                         : Quits the program." << std::endl;
            std::cout << "Please enter your command: ";
            std::cout << std::endl;
        }
};

class CommandHandler
{
public:
    // Constructor that initializes CommandHandler with a reference to a Dictionary object
    CommandHandler(Dictionary& dict) : dictionary(dict) {}

    // Function to process the command entered by the user.
    // It handles various commands like 'add', 'del', 'find', and 'prefix'.
    void handleCommand(const std::string& cmdString)
    {
        std::istringstream line(cmdString);
        std::string cmd, word, translation;
        line >> cmd;
        line >> word;
        word = toLower(word);

        if (cmd == "prefix")
        {
            auto wordsWithPrefix = dictionary.findWordsWithPrefix(word);
            if (!wordsWithPrefix.empty())
            {
                std::cout << "Words starting with the prefix '" << word << "':\n";
                for (auto& wordPtr : wordsWithPrefix)
                {
                    std::cout << '"' << wordPtr->name << '"' << "->";
                    wordPtr->printTranslations();
                }
            }
            else
            {
                std::cout << "No words found with the prefix '" << word << "'.\n";
            }
        }
        else
        {
            Word* wordObject = dictionary.findWord(word);

            if (cmd == "add")
            {
                if (wordObject == nullptr)
                {
                    dictionary.addWord(word);
                    wordObject = &dictionary.words.back();
                    std::cout << "Added a new word: " << word << '\n';
                }

                while (line >> translation)
                {
                    translation = toLower(translation);
                    wordObject->translations.push_back(translation);
                    std::cout << "Added translation: " << translation << '\n';
                }

                wordObject->sortTranslationsByLength();
            }
            else if (cmd == "del")
            {
                std::vector<std::string> translationsToDelete;
                while (line >> translation)
                {
                    translation = toLower(translation);
                    translationsToDelete.push_back(translation);
                }

                if (translationsToDelete.empty())
                {
                    if (wordObject != nullptr)
                    {
                        dictionary.deleteWord(wordObject);
                        std::cout << "Deleted the word: " << word << '\n';
                    }
                    else
                    {
                        std::cout << "Word not found.\n";
                    }
                }
                else
                {
                    if (wordObject != nullptr)
                    {
                        dictionary.deleteWordTranslations(wordObject, translationsToDelete);
                        std::cout << "Deleted translations for the word: " << word << '\n';
                    }
                    else
                    {
                        std::cout << "Word not found.\n";
                    }
                }
            }
            else if (cmd == "find")
            {
                if (wordObject != nullptr)
                {
                    std::cout << "Found the word: " << word << '\n';
                    wordObject->printTranslations();
                }
                else
                {
                    std::cout << "Word not found.\n";
                }
            }
            else if (cmd == "prefix")
            {
                if (wordObject != nullptr)
                {
                    std::cout << "Found the word: " << word << '\n';
                    wordObject->printTranslations();
                }
                else
                {
                    std::cout << "Word not found.\n";
                }
            }
            else
            {
                std::cout << "Invalid command. Please try again.\n";
            }
        }
    }
    // Utility function to convert a string to lower case
    std::string toLower(const std::string& input)
    {
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

private:
    // Reference to a Dictionary object for manipulation
    Dictionary& dictionary;
};

// The main function, where the program execution begins
int main()
{
    Dictionary dictionary;
    CommandHandler cmdHandler(dictionary);

    for (;;)
    {
        std::string command = UI::getInputCommand();
        if (command == "quit")
        {
            std::cout << "Exiting the program. Goodbye!\n";
            break;
        }
        cmdHandler.handleCommand(command);
    }
    return 0;
}



