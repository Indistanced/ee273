#pragma once

#include "Player.h"

// Class created using singleton design pattern, which permits only one instance to be created
class Game {
public:
	static Game* getInstance(Player* p);
	void start(Player* p);
private:
	static Game* instance;
	Player* p;

	Game(Player* p) : p(p) {};

	// Delete copy constructor and copy assignment operators
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
};