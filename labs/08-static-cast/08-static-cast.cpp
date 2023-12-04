// Name of the file: 08-static-cast.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// Using of static_cast for type conversion of pointers within a class hierarchy in C++

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <memory>

enum class ObjectType
{
	Regular, Uniq
};

struct RegularItem
{
	std::string name;
	ObjectType type;
	RegularItem(const std::string& name_) : name(name_), type(ObjectType::Regular)
	{

	}
	virtual ~RegularItem() {}
};

using ItemPointer = std::shared_ptr<RegularItem>;

struct UniqItem : public RegularItem
{
	int price;
	UniqItem(const std::string& name_, int price_) : RegularItem(name_), price(price_)
	{
		type = ObjectType::Uniq;
	}
};

int main()
{
	// Items.
	std::vector<ItemPointer> items;
	items.emplace_back(std::make_shared<RegularItem>("Sword"));
	items.emplace_back(std::make_shared<UniqItem>("Fork of Truth", 12));
	items.emplace_back(std::make_shared<RegularItem>("Shield"));

	// Print name and price of all uniq items. Use with caution!!	
	std::cout << "Uniq items (Fork of Truth:12):" << std::endl;
	for (auto&& item : items)
	{
		// to be sure that it is an instance of the UniqItem class
		if (item->type == ObjectType::Uniq)
		{
			// static_cast
			UniqItem* uniqItem = static_cast<UniqItem*>(item.get());
			std::cout << uniqItem->name << ":" << uniqItem->price << std::endl;
		}
	}
}
