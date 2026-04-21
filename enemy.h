//Author:  Kyle Simpson
//Creation Date: 07/04/26

//Changes made:
//- updated to include weakness for combat

#pragma once
#include <string>
#include "character.h"

class Enemy : public Character {

public:
	//constuctor using Character inheratance 
	Enemy(std::string name, int maxHealth, int strength, std::string element) : Character(name, maxHealth, maxHealth, strength) { this->element = element; }

	//getters
	std::string get_element() { return element; }

	std::string get_weakness_element() {  //retuns the enemys weakness using their assinged element 
		if (element == "water") return "grass";
		else if (element == "fire") return "water";
		else if (element == "grass") return "fire";
		else return "none";
	}

private:
	std::string element;
};
