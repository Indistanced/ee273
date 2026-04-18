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
	
	while (true) {
	Player* p = nullptr;
	p = selectPlayerInstance(p);
	if (p == nullptr) {
		return 0; // Check whether player exists
	}

	Game* g = Game::getInstance(p); // Create, load, or exit instance
	bool alive = g->run(g, p);

	// TESTING
	Level::test();
	
	delete g;
	Game::resetInstance();
	delete p;

	if(!alive) {
		if (gameOverMenu()) {
			continue; // restart
		}
		else {
			break; // quit game
		}
	}
	else {
		break; // normal exit
	}

	return 0;
}