#include <iostream> // Read and write functionality

#include "Player.h"
#include "menu.h"
#include "main.h"

Game* Game::instance = nullptr; // Tells class that the game initially hasn't been created

Game* Game::getInstance(Player* p) {
	if (instance == nullptr) { // If game hasn't been created yet
		instance = new Game(p); // Create an instance of the game
	} return instance;
}

void Game::start(Player* p) {
	std::cout << "Welcome, " << p->getName() << '\n';
	std::cout << "Health: (" << p->getHealth() << "/" << p->getMaxHealth() << ")\n"; // Health bar check
	std::cout << "Location: " << p->location;
}

int main() {
	Player* p1 = selectPlayerInstance(p1);
	if (p1 == nullptr) return 0; // Checks whether player exists

	Game* g = Game::getInstance(p1);
	g->start(p1);

	delete p1;
	delete g;

	return 0;
}