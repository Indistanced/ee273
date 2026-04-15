#include "Player.h"
#include "menu.h"
#include "Game.h"
#include "unicode.h"
#include "Game_Level.h"

#include <ctime>

int main() {
	
	// INITIALISATIONS

	srand(time(0)); // Random number generator set seed
	unicode_init(); // Enable unicode

	Player* p = selectPlayerInstance(p); // Select game type
	if (p == nullptr) return 0; // Check whether player exists

	Game* g = Game::getInstance(p); // Create, load, or exit instance

	// MAIN

	g->run(g, p); // Run game instance

	// TESTING

	Level::test();

	// DEALLOCATE MEMORY

	delete p;
	delete g;

	return 0;
}