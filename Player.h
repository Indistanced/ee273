#pragma once

#include "Character.h"

class Player : public Character {
public:
	// Inherit constructor initialisations from Character class
	Player(std::string name) : Character{ name } {};
	Player(std::string name, int hp) : Character{ name, hp } {};
};