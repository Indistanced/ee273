#pragma once
#include <string>

class Character {

protected:
	std::string name;
	unsigned int health;
	unsigned int maxHealth;

public:

	Character(std::string Name);
	Character(std::string Name, int hp);
	virtual ~Character();

	virtual int Attack();
	void takeDamage(int dmg);
	bool isAlive() const;

	std::string getName();
	int getHealth();
};
