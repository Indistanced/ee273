#include <iostream>

#include "Game_Level.h"

int Level::test() {
	Level& l = Level::getInstance();
	Level& l2 = Level::getInstance();

	try {
		if (&l != &l2) throw std::logic_error("\nTest: Invalid game level state\n\n");
		else std::cout << "\nTest: Valid game level state (only one instance)\n\n";
	} catch (std::logic_error &e) { 
		std::cerr << e.what();
	}
}

void Level::isCompleteString() {
	std::cout << "[ ";
	for (int i{}; i < NUMBER_OF_LEVELS; i++) {
		std::cout << this->isComplete[i] << ", ";
		if (i < NUMBER_OF_LEVELS - 1) {
			std::cout << ", ";
		} else std::cout << " ]";
	}
}