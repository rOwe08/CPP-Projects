// Name of the file: 03-dictionary.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// Implementation of a translation dictionary with basic operations

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Word class to store the word and its translations
class Word
{
public:
    std::string name;
    std::vector<std::string> translations;
};

// Function to find a word in the dictionary and return its pointer
// Return nullptr if not found
Word* findWordInDictionary(const std::string& word, std::vector<Word>& dictionary)
{
    for (auto& entry : dictionary)
    {
        if (entry.name == word)
        {
            return &entry;
        }
    }
    return nullptr;
}

// Function to print the User Interface Menu
void printUIMenu()
{
    std::cout << "\n--- Available Commands ---\n";
    std::cout << "add [word] [translations...] : Adds a word and its translations.\n";
    std::cout << "del [word] [translations...] : Deletes a word or its specific translations.\n";
    std::cout << "find [word]                  : Finds a word and prints its translations.\n";
    std::cout << "quit                         : Quits the program.\n";
    std::cout << "Please enter your command: ";
}

// Function to add a word to the dictionary
void addWordToDictionary(const std::string& word, std::vector<Word>& dictionary)
{
    Word newWord;
    newWord.name = word;
    dictionary.push_back(newWord);
}

// Function to delete a word from the dictionary
void deleteWordInDictionary(Word* wordObject, std::vector<Word>& dictionary)
{
    auto position = wordObject - &dictionary[0];
    if (position >= 0 && position < dictionary.size())
    {
        dictionary.erase(dictionary.begin() + position);
    }
}

// Function to delete specific translations of a word from the dictionary
void deleteWordTranslationsInDictionary(Word* wordObject, const std::vector<std::string>& translationsToDelete)
{
    for (const auto& translation : translationsToDelete)
    {
        wordObject->translations.erase(std::remove(wordObject->translations.begin(), wordObject->translations.end(), translation), wordObject->translations.end());
    }
}

// Function to print the translations of a word
void printTranslations(const Word& wordObject)
{
    std::cout << "Translations: ";
    for (const auto& translation : wordObject.translations)
    {
        std::cout << translation << ' ';
    }
    std::cout << std::endl;
}

// The main function, where the program execution begins
int main()
{
    std::string r, cmd, word, translation;
    std::vector<Word> dictionary;

    for (;;)
    {
        printUIMenu();

        getline(std::cin, r);
        if (std::cin.fail())
        {
            break;
        }

        std::istringstream line(r);
        line >> cmd;

        if (cmd == "quit")
        {
            std::cout << "Exiting the program. Goodbye!\n";
            break;
        }

        line >> word;
        Word* wordObject = findWordInDictionary(word, dictionary);

        if (cmd == "add")
        {
            if (wordObject == nullptr)
            {
                addWordToDictionary(word, dictionary);
                wordObject = &dictionary.back();
                std::cout << "Added a new word: " << word << '\n';
            }

            while (line >> translation)
            {
                wordObject->translations.push_back(translation);
                std::cout << "Added translation: " << translation << '\n';
            }
        }
        else if (cmd == "del")
        {
            std::vector<std::string> translationsToDelete;
            while (line >> translation)
            {
                translationsToDelete.push_back(translation);
            }

            if (translationsToDelete.empty())
            {
                if (wordObject != nullptr)
                {
                    deleteWordInDictionary(wordObject, dictionary);
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
                    deleteWordTranslationsInDictionary(wordObject, translationsToDelete);
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
                printTranslations(*wordObject);
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

    return 0;
}



