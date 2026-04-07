#pragma once

#include "Character.h"
#include "Inventory.h"
#include "Enemy.h"

#include <vector>
#include <utility>
#include <iostream>

class Player : public Character {
public:

	const unsigned int DEFAULT_LEVEL = 1;
	std::string location;
	const std::string START_LOCATION = "Town";
	const int START_EXP = 0;
	

	// Inherit constructor initialisations from Character class
	Player(std::string name) : Character{ name } { this->level = DEFAULT_LEVEL; location = START_LOCATION; exp = START_EXP; };
	Player(std::string name, int hp) : Character{ name, hp } { level = DEFAULT_LEVEL; location = START_LOCATION; exp = START_EXP; };
	Player(std::string name, int hp, int maxHp, int strength) : Character{ name, hp, maxHp, strength} { level = DEFAULT_LEVEL; location = START_LOCATION; exp = START_EXP; };
	Player(std::string name, int hp, int maxHp, int strength, std::string location, int level, int exp): Character{ name, hp, maxHp, strength} 
	{this-> level = level, this->location = location; this->exp = exp;};

	static std::istream& pin(Player* p);
	void to_string();

	int getLevel() const { return level; };
	void addExp(int exp_ammount);
	int getExp() const { return exp; };

	Inventory& getInventory() { return inventory; } //get players inventroy 

	std::vector<std::pair<std::string, bool>>& getQuests();
	bool addQuest(std::string description, bool complete);
	bool completeQuest(std::string description);
	void quests_to_string();
	int questNumber();

private:
	unsigned int level;
	unsigned int exp;
	unsigned int exp_limit = 100;
	Inventory inventory; // player has an inventory 
	std::vector<std::pair<std::string, bool>> quest; 
};