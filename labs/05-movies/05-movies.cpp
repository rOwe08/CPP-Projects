// Name of the file: 05-movies.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// Representation and construction of movies and imput from csv file

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <string>

// The Movie class represents a movie with its details.
class Movie
{
private:
    std::string name;
    unsigned short year;
    std::string genre;
    unsigned short rating;
    std::set<std::string> actorsNames;

    // Splits a string by a delimiter into a set of substrings.
    static std::set<std::string> splitToSet(const std::string& str, char delimiter)
    {
        std::set<std::string> resultSet;
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delimiter))
        {
            resultSet.insert(token);
        }
        return resultSet;
    }

public:
    // Constructor to initialize a Movie object
    Movie(const std::string& name, unsigned short year, const std::string& genre, unsigned short rating, const std::set<std::string>& actorsNames)
        : name(name), year(year), genre(genre), rating(rating), actorsNames(actorsNames)
    {
    }

    // Converts the movie details to a JSON string.
    std::string toJson() const
    {
        std::string json = "{ ";
        json += "\"name\": \"" + name + "\", ";
        json += "\"year\": " + std::to_string(year) + ", ";
        json += "\"genre\": \"" + genre + "\", ";
        json += "\"rating\": " + std::to_string(rating);
        if (!actorsNames.empty())
        {
            json += ", \"actors\": [";
            for (auto it = actorsNames.begin(); it != actorsNames.end(); ++it)
            {
                if (it != actorsNames.begin()) json += ", ";
                json += "\"" + *it + "\"";
            }
            json += "]";
        }
        json += " }";
        return json;
    }

    // Static function to import from a CSV file
    static bool import_csv(const std::string& filename, std::vector<Movie>& movies)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return false;
        }

        return import_csv(file, movies);
    }

    // Static function to import from an input stream
    static bool import_csv(std::istream &stream, std::vector<Movie> &movies)
    {
        std::string line;
        std::getline(stream, line);

        while (std::getline(stream, line))
        {
            std::stringstream linestream(line);
            std::string cell;
            std::vector<std::string> cells;

            while (std::getline(linestream, cell, ';'))
            {
                cells.push_back(cell);
            }

            std::string name = cells[0];
            unsigned short year = std::stoi(cells[1]);
            std::string genre = cells[2];
            unsigned short rating = std::stoi(cells[3]);
            std::set<std::string> actors = splitToSet(cells[4], ',');

            movies.emplace_back(std::move(name), year, std::move(genre), rating, std::move(actors));
        }

        return true;
    }

    const std::string &getName() const { return name; }
    unsigned short getYear() const { return year; }
    const std::string &getGenre() const { return genre; }
    unsigned short getRating() const { return rating; }
    const std::set<std::string> &getActorsNames() const { return actorsNames; }

    void setName(const std::string &newName) { name = newName; }
    void setYear(unsigned short newYear) { year = newYear; }
    void setGenre(const std::string &newGenre) { genre = newGenre; }
    void setRating(unsigned short newRating) { rating = newRating; }
    void setActorsNames(const std::set<std::string> &newActorsNames) { actorsNames = newActorsNames; }
};

// Prints all movies in the list in JSON format.
void query_and_print_all(const std::vector<Movie> &movies)
{
    for (const auto &movie : movies)
    {
        std::cout << movie.toJson() << std::endl;
    }
}

// Queries and prints all movies that are older than a certain year and include a specific actor.
void query_older_with_actor_print_all(const std::vector<Movie> &movies, unsigned short year, const std::string &actor)
{
    for (const auto &movie : movies)
    {
        if (movie.getYear() < year && movie.getActorsNames().count(actor) > 0)
        {
            std::cout << movie.toJson() << std::endl;
        }
    }
}

int main()
{
    std::vector<Movie> movies;

    movies.push_back(Movie("Final Fantasy: The Spirits Within", 2001, "Animation/Science Fiction", 67, { "Alec Baldwin", "Ving Rhames", "Ming-Na Wen" }));
    movies.push_back(Movie("The Wolf of Wall Street", 2013, "Biography/Crime/Drama", 83, { "Leonardo DiCaprio", "Jonah Hill", "Margot Robbie" }));

    Movie aMovie("Inception", 2010, "Action/Adventure/Sci-Fi", 86, { "Leonardo DiCaprio", "Joseph Gordon-Levitt", "Ellen Page" });
    movies.push_back(std::move(aMovie));

    movies.emplace_back("Interstellar", 2014, "Adventure/Drama/Sci-Fi", 85, std::set<std::string>{"Matthew McConaughey", "Anne Hathaway", "Jessica Chastain"});       ////GOAT:)

    movies.push_back(Movie("Catch Me If You Can", 2002, "Biography/Crime/Drama", 81, { "Leonardo DiCaprio", "Tom Hanks", "Christopher Walken" }));
    movies.push_back(Movie("Django Unchained", 2012, "Drama/Western", 81, { "Jamie Foxx", "Christoph Waltz", "Leonardo DiCaprio" }));

    //for (const Movie& film : movies)
    //{
    //    std::cout << film.toJson() << std::endl;
    //}

    //// Import movies from a CSV file
    // 
    //std::string inputFile;
    //bool result = Movie::import_csv(inputFile, movies);
    //if (result)
    //{
    //    for (const Movie& movie : movies)
    //    {
    //        std::cout << movie.toJson() << std::endl;
    //    }
    //}

    std::cout << "All movies in JSON format:" << std::endl;
    query_and_print_all(movies);

    std::cout << "\nMovies before a certain year with a specific actor:" << std::endl;
    query_older_with_actor_print_all(movies, 2004, "Leonardo DiCaprio");

}
