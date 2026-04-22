//Author:  Kyle Simpson
//Creation Date: 07/04/26

//Changes made:
//- Include weakness for combat sequence

#pragma once
#include <string>
#include "character.h"

class Enemy : public Character {

public:
	// Constructor using Character inheritance 
	Enemy(std::string name, int maxHealth, int strength, std::string element) : Character(name, maxHealth, maxHealth, strength) { this->element = element; }

	// Getters
	std::string get_element() { return element; }

	 // Return the enemy's weakness using their assigned element 
	std::string get_weakness_element() { 
		if (element == "water") return "grass";
		else if (element == "fire") return "water";
		else if (element == "grass") return "fire";
		else return "none";
	}

private:
	std::string element;
};
