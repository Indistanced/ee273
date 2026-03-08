#pragma once

#include <string>

class Character {
public:
	// Default variables
	const unsigned int DEFAULT_MAX_HEALTH = 100;
	const unsigned int DEFAULT_STRENGTH = 5;

	// Constructor variations
	Character(std::string name) : name(name), currentHealth(DEFAULT_MAX_HEALTH), maxHealth(DEFAULT_MAX_HEALTH), strength(DEFAULT_STRENGTH) {};
	Character(std::string name, int hp) : name(name), currentHealth(hp), maxHealth(DEFAULT_MAX_HEALTH), strength(DEFAULT_STRENGTH) {};
	Character(std::string name, int hp, int maxHp, int strength) : name(name), currentHealth(hp), maxHealth(maxHp), strength(strength) {};

	virtual ~Character() {}; // Destructor

	// Getter member functions
	std::string getName() const { return name; };
	int getHealth() const { return currentHealth; };
	int getMaxHealth() const { return maxHealth; };
	int getStrength() const { return strength; };

	// General member functions
	virtual int Attack();
	void takeDamage(int dmg);
	bool isAlive() const;

protected:
	std::string name;
	unsigned int currentHealth;
	unsigned int maxHealth;
	unsigned int strength;
};