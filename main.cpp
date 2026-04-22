//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 01/03/26

//Changes made:
//- Add in pseudorandom number generator seed
//- Add unicode enable  

#include "Player.h"
#include "menu.h"
#include "Game.h"
#include "unicode.h"
#include "Game_Level.h"
#include "main.h"
#include "Minimap.h"

#include <thread>
#include <ctime>
#include <array>
#include <map>

#include <Windows.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

bool running = true;
Player* p = nullptr;

int gameLoop() {
	while (running) {
		p = selectPlayerInstance(p);
		if (p == nullptr) {
			return 0; // Check whether player exists
		}

		Game* g = Game::getInstance(p); // Create, load, or exit instance
		bool alive = g->run(g, p);

		// TESTING
		//Level::test();

		delete g;
		Game::resetInstance();
		if (!p->isAlive()) {
			if (gameOverMenu(p)) { // IF RESTART
				delete p;
				continue;
			}
			else { // IF EXIT GAME
				running = false;
				delete p;
				return 0;
			}
		}
	}
}

int main() {
	// INITIALISATIONS;
	srand(static_cast<unsigned int>(time(0))); // Random number generator set seed
	unicode_init(); // Enable unicode

	std::thread t1(gameLoop);
	std::thread t2(Minimap::mapLoop);

	t1.join();
	t2.join();
}