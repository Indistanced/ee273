#include "Player.h"
#include "menu.h"
#include "Game.h"
#include "unicode.h"

int main() {
	unicode_init();

	Player* p = selectPlayerInstance(p);
	if (p == nullptr) return 0; // Checks whether player exists

	Game* g = Game::getInstance(p); // Creates, loads, or exits instance
	g->run(g, p);

	delete p;
	delete g;

	return 0;
}