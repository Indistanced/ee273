#pragma once

#include "Character.h"

class Player : public Character {
public:
	std::string location;
	const std::string START_LOCATION = "Town";
<<<<<<< HEAD
	
=======

>>>>>>> 1a7cf2b09a8864ec2b58283c6edb0fd63a4be372

	// Inherit constructor initialisations from Character class
	Player(std::string name) : Character{ name } { location = START_LOCATION; };
	Player(std::string name, int hp) : Character{ name, hp } { location = START_LOCATION; };
<<<<<<< HEAD
	Player(std::string name, int hp, int maxHp, int strength) : Character{ name, hp, maxHp, strength } { location = START_LOCATION;};
	Player(std::string name, int hp, int maxHp, int strength, std::string location) : Character{ name, hp, maxHp, strength } { this->location = location;};


=======
	Player(std::string name, int hp, int maxHp, int strength) : Character{ name, hp, maxHp, strength } { location = START_LOCATION; };
	Player(std::string name, int hp, int maxHp, int strength, std::string location) : Character{ name, hp, maxHp, strength } { this->location = location; };

	static std::istream& pin(Player* p);
>>>>>>> 1a7cf2b09a8864ec2b58283c6edb0fd63a4be372
};