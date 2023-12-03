#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <format>

struct Position
{
	int x;
	int y;
};

struct Person
{
	std::string name;
	int money;
	Position position;
	bool active = true;
};

std::vector<Person> generate_people()
{
	return {
		{"Ailish", 10000, {0, 0}},
		{"Larcel", -12, {0, 0}, false},
		{"Nicolas", -1, {12, 17}, false},
		{"Brut", 12, {12, 18}},
	};
}


int main()
{
	auto people = generate_people();

	// Count number of people with negative money.
	// std::count, std::cout_if
	size_t count = 0; // TODO
	std::cout << "People with negative money (2): " << count << std::endl;

	// Find person with positive money after someone with negative money.
	// std::find, std::find_if, std::find_if_not, functor
	// TODO
	auto result = people.end();
	if (result != people.end())
	{
		std::cout << "Person found (Brut): " << result->name << std::endl;
	}

	std::vector<Person> vip;
	// Copy people with more then 1000 money to vip list.
	// std::copy, std::copy_if, std::back_inserter
	// TODO
	std::cout << "VIP count (1): " << vip.size() << std::endl;

	// Sort people by money.
	// std::sort
	// TODO

	// Print name of every person without using for-cycle.
	// std::for_each, std::for_each_n
	std::cout << "People (Ailish, Brut, Nicolas, Larcel):" << std::endl;
	// TODO

	// Remove inactive people from the peoples.
	// std::remove, std::remove_if, people.erase	
	// TODO

	// Print all remaining people.
	std::cout << "Active people (Ailish, Brut):" << std::endl;
	for (auto&& person : people)
	{
		std::cout << "  " << person.name << std::endl;
	}

	// Create list of positions.
	// std::transform, std::back_inserter
	std::vector<Position> positions;
	// TODO

	// Print positions.
	std::cout << "Positions (0:0, 12:18):" << std::endl;
	for (auto&& position : positions)
	{
		std::cout << std::format("  {}:{}", position.x, position.y) << std::endl;
	}

}