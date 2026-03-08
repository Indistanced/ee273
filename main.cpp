#include <iostream> // Read and write functionality

#include "Player.h"
#include "menu.h"

int main() {

	Player* player_1 = menu();

	if (player_1 == nullptr) {
		return 0;
	}

	std::cout << "Welcome Adventure!\n";
	std::cout << player_1->getName() << "\n"; // print name test
	std::cout << "Health: (" << player_1->getHealth() << "/" << player_1->getMaxHealth() << ")\n"; // health bar check
	std::cout << "Location: " << player_1->location;


	delete player_1;

	return 0;
}