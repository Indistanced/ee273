#pragma once

#include "Character.h"

class Player : public Character {
public:

	std::string location;
	const std::string START_LOCATION = "Town";
	const int START_EXP = 0;

	// Inherit constructor initialisations from Character class
	Player(std::string name) : Character{ name } { location = START_LOCATION; exp = START_EXP; };
	Player(std::string name, int hp) : Character{ name, hp } { location = START_LOCATION; exp = START_EXP;};
	Player(std::string name, int hp, int maxHp, int strength) : Character{ name, hp, maxHp, strength} { location = START_LOCATION; exp = START_EXP;};
	Player(std::string name, int hp, int maxHp, int strength, std::string location, int level, int exp) 
		: Character{ name, hp, maxHp, strength, level} {this->location = location; this->exp = exp;};

	static std::istream& pin(Player* p);
	void to_string();

	void addExp(int exp_ammount);
	int getExp() const { return exp;};

private:
	unsigned int exp;
	unsigned int exp_limit = 100;

};