//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 02/03/26

//Changes made:
//- added in location attribute
//- added in Level and experience attribute
//- added in Inventory and quest management

#pragma once

#include "Character.h"
#include "Inventory.h"
#include "Enemy.h"

#include <vector>
#include <utility>
#include <iostream>

class Player : public Character {
public:

	// Default variables
	const unsigned int DEFAULT_LEVEL = 1;
	const std::string START_LOCATION = "Town";
	const int START_EXP = 0;
	const int DEFAULT_EXP_LIMIT = 100;


	// Inherit constructor initialisations from Character class
	Player(std::string name) : Character{ name } { this->level = DEFAULT_LEVEL; this->location = START_LOCATION; this->exp = START_EXP; this->expLimit = DEFAULT_EXP_LIMIT; }
	Player(std::string name, int hp) : Character{ name, hp } { this->level = DEFAULT_LEVEL; this->location = START_LOCATION; this->exp = START_EXP; this->expLimit = DEFAULT_EXP_LIMIT; }
	Player(std::string name, int hp, int maxHp, int strength) : Character{ name, hp, maxHp, strength } {
		this->level = DEFAULT_LEVEL; this->location = START_LOCATION; this->exp = START_EXP; this->expLimit = DEFAULT_EXP_LIMIT;
	}
	Player(std::string name, int hp, int maxHp, int strength, std::string location, int level, int exp, int expLimit) : Character{ name, hp, maxHp, strength }
	{
		this->level = level, this->location = location; this->exp = exp; this->expLimit = expLimit;
	};


	static std::istream& pin(Player* p);  // function to call player name before test i.e "John: "

	void to_string(); // convert player stats to string

	// Getters 
	int getLevel() const { return level; };
	int getExp() const { return exp; };
	int getExpLimit() const { return expLimit; }
	std::string getLocation() { return location; };
	Inventory& getInventory() { return inventory; } // Get Player inventory 
	std::vector<std::pair<std::string, bool>>& getQuests();

	// Setters
	void addExp(int exp_ammount);
	void setLocation(std::string loc) { this->location = loc; };

	// Quest management functions
	bool addQuest(std::string description, bool complete);
	bool completeQuest(std::string description);
	void quests_to_string();
	int questNumber();

private:
	unsigned int level;
	unsigned int exp;
	unsigned int expLimit;
	std::string location;
	Inventory inventory; // player has an inventory 
	std::vector<std::pair<std::string, bool>> quests;
};