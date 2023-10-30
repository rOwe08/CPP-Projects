// Name of the file: 04-movies.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// Implementation of a movie database

#include <iostream>
#include <vector>
#include <algorithm>

// Class representing a film
class Film
{
private:
    std::string name;
    std::string director;
    int year;

public:
    // Constructor initializing the film's properties
    Film(std::string n, std::string d, int y) : name(n), director(d), year(y) {}

    // Getter methods for the film's properties
    std::string getName() const { return name; }
    std::string getDirector() const { return director; }
    int getYear() const { return year; }

    // Internal comparator using < operator, for sorting based on year and then name
    bool operator<(const Film &other) const
    {
        if (year != other.year)
            return year < other.year;
        return name < other.name;
    }
    // Function to print the film's details
    void printDetails() const
    {
        std::cout << name << ", directed by " << director << ", released in " << year << std::endl;
    }
};

// Function to populate the films vector
void addFilms(std::vector<Film> *films)
{
    // Sample data of films
    films->push_back(Film("Pulp Fiction", "Quentin Tarantino", 1994));
    films->push_back(Film("Shawshank Redemption", "Frank Darabont", 1994));
    films->push_back(Film("Star Wars: A New Hope", "George Lucas", 1977));
    films->push_back(Film("The Dark Knight", "Christopher Nolan", 2008));
    films->push_back(Film("Forrest Gump", "Robert Zemeckis", 1994));
    films->push_back(Film("Jurassic Park", "Steven Spielberg", 1993));
    films->push_back(Film("Blade Runner", "Ridley Scott", 1982));
    films->push_back(Film("Fight Club", "David Fincher", 1999));
    films->push_back(Film("Interstellar", "Christopher Nolan", 2014));
}

// Function to print all films in the vector
void printFilms(const std::vector<Film> &films)
{
    for (const Film& film : films)
    {
        film.printDetails();
    }
}

// External comparator using functor, for sorting by film year and then name
struct CompareByYearThenName
{
    bool operator()(const Film &a, const Film &b) const
    {
        if (a.getYear() != b.getYear())
            return a.getYear() < b.getYear();

        return a.getName() < b.getName();
    }
};

// Function using the functor for sorting
void sortExternalComparatorFunctor(std::vector<Film> *films)
{
    std::sort(films->begin(), films->end(), CompareByYearThenName());

    std::cout << "\nFilms after sorting by year and name (External comparator (functor)):\n";
    printFilms(*films);
}

// Function using a lambda for sorting
void sortExternalComparatorLambda(std::vector<Film> *films)
{
    auto comparator = [](const Film &a, const Film &b) -> bool
    {
        if (a.getYear() != b.getYear())
            return a.getYear() < b.getYear();
        return a.getName() < b.getName();
    };

    std::sort(films->begin(), films->end(), comparator);

    std::cout << "\nFilms after sorting by year and name (Lambda function):\n";
    printFilms(*films);
}

// Function using the internal comparator for sorting
void sortInternalComparator(std::vector<Film> *films)
{
    std::sort(films->begin(), films->end());

    std::cout << "\nFilms after sorting by year and name (Internal comparator):\n";
    printFilms(*films);
}

// External standard function comparator for sorting
bool compareFilms(const Film &a, const Film &b)
{
    if (a.getYear() != b.getYear())
        return a.getYear() < b.getYear();
    return a.getName() < b.getName();
}

// Function using the standard function for sorting
void sortExternalComparatorFunction(std::vector<Film> *films)
{
    std::sort(films->begin(), films->end(), compareFilms);

    std::cout << "\nFilms after sorting by year and name (Standard function):\n";
    printFilms(*films);
}

int main()
{
    std::vector<Film> films;
    addFilms(&films);

    std::cout << "Films before sorting:\n";
    printFilms(films);

    // Using different comparators to sort and then clearing the vector for next sort:
    sortExternalComparatorFunctor(&films);
    films.clear();
    addFilms(&films);

    sortExternalComparatorLambda(&films);
    films.clear();
    addFilms(&films);

    sortExternalComparatorFunction(&films);
    films.clear();
    addFilms(&films);

    sortInternalComparator(&films);
    films.clear();

    return 0;
}
