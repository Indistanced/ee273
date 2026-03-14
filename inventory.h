#pragma once
#include <utility> // added for pair
#include <vector>
#include <string>

#include "player.h"

class Inventory {
public:

	bool addItem(std::string item);
	bool removeItem(std::string item);
	bool useItem(std::string item);
	void displayItems();


private:
	std::vector<std::pair<std::string, std::string>> items; // item with a name and a description.

};