//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 01/03/26

//Changes made:
//- added in random number generator seed
//- added unicode enable  

#include "Player.h"
#include "menu.h"
#include "Game.h"
#include "unicode.h"
#include "Game_Level.h"
#include "win.h"
#include <thread>

#include <ctime>

int main() {
	
	// INITIALISATIONS
	WinMinimap();

	srand(static_cast<unsigned int>(time(0))); // Random number generator set seed
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