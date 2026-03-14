#pragma once
#include <string>
#include "character.h";

class Enemy : public Character {

public:
	Enemy(std::string name, int health) : Character(name, health) {}

protected:

};