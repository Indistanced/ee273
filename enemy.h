#pragma once
#include <string>
#include "character.h"

class Enemy : public Character {

public:
	Enemy(std::string name ,int maxHealth, int strength, std::string element) : Character(name, maxHealth, maxHealth, strength) { this->element = element;}

	std::string get_element() { return element;}

	std::string get_weakness_element() {
		if (element == "water") {
			return "grass";
		}
		else if (element == "fire") {
			return "water";
		}
		else if (element == "grass") {
			return "fire";
		}
		else {
			return "none";
		}
	}

private:
	std::string element;

};
