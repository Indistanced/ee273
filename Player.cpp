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
	std::cout << "Strength: " << this->strength << "\n";
	std::cout << "Location: " << this->location << "\n";
}