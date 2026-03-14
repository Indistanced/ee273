#include "Player.h"

#include <fstream>
#include <iostream>

std::istream& Player::pin(Player* p) {
	std::cout << p->getName() << ": ";
	return std::cin;
}

void Player::to_string() {

	std::cout << "Name: " << this->name << "\n";
	std::cout << "Health: " << "(" << this->currentHealth << "/" << this->maxHealth << ")\n";
	std::cout << "Level: " << this->level << "\n";
	std::cout << "Exp: " << "(" << this->exp << "/" << this->exp_limit << ")\n";
	std::cout << "Strength: " << this->strength << "\n";
	std::cout << "Location: " << this->location << "\n";

}

void Player::addExp(int exp_ammount) {

	exp += exp_ammount;

	if (exp >= exp_limit) {

		level++;
		exp = exp - exp_limit;
		maxHealth += 20;
		strength += 10;
		currentHealth = maxHealth;

		std::cout << "-- You leveled up! --\n";
	}
}