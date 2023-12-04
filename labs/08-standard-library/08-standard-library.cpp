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
	// std::count, std::count_if
	size_t count = 0;
	count = std::count_if(people.begin(), people.end(), [](const Person& p) { return p.money < 0; });
	std::cout << "People with negative money (2): " << count << std::endl;
	std::cout << std::endl;

	// Find person with positive money after someone with negative money.
	// std::find, std::find_if, std::find_if_not, functor
	auto result = people.end();

	result = std::adjacent_find(people.begin(), people.end(),
		[](const Person& a, const Person& b) { return a.money < 0 && b.money > 0; });

	if (result != people.end())
	{
		result++;
	}
	if (result != people.end())
	{
		std::cout << "Person found (Brut): " << result->name << std::endl;
	}
	std::cout << std::endl;

	// Copy people with more then 1000 money to vip list.
	// std::copy, std::copy_if, std::back_inserter
	std::vector<Person> vip;
	std::copy_if(people.begin(), people.end(), std::back_inserter(vip), [](const Person& p) { return p.money > 1000; });
	std::cout << "VIP count (1): " << vip.size() << std::endl;
	std::cout << std::endl;

	// Sort people by money.
	// std::sort
	std::sort(people.begin(), people.end(), [](const Person& a, const Person& b) { return a.money > b.money; });

	// Print name of every person without using for-cycle.
	// std::for_each, std::for_each_n
	std::cout << "People (Ailish, Brut, Nicolas, Larcel):" << std::endl;
	std::for_each(people.begin(), people.end(), [](const Person& p) { std::cout << p.name << " "; });
	std::cout << std::endl << std::endl;

	// Remove inactive people from the peoples.
	// std::remove, std::remove_if, people.erase	
	people.erase(std::remove_if(people.begin(), people.end(), [](const Person& p) { return !p.active; }), people.end());

	// Print all remaining people.
	std::cout << "Active people (Ailish, Brut):" << std::endl;
	for (auto&& person : people)
	{
		std::cout << person.name << " ";
	}

	std::cout << std::endl;

	// Create list of positions.
	// std::transform, std::back_inserter
	std::vector<Position> positions;
	std::transform(people.begin(), people.end(), std::back_inserter(positions),
		[](const Person& p) { return p.position; });
	std::cout << std::endl;

	// Print positions.
	std::cout << "Positions (0:0, 12:18):" << std::endl;
	for (auto&& position : positions)
	{
		std::cout << std::format("  {}:{}", position.x, position.y) << std::endl;
	}
}