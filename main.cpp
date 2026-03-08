#include <iostream> // Read and write functionality

#include "Player.h"
#include "menu.h"

int main() {
	std::string name;

	menu();
	Player* p1 = new Player(name);
	std::cout << p1->getStrength(); // 5 (test stimulus)

	return 0;
}