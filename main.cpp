#include <iostream> // Read and write functionality

#include "Player.h"

int main() {
	std::string name;

	Player* p1 = new Player(name);
	std::cout << p1->getStrength(); // 5 (test stimulus)
}