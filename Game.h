#pragma once

#include "Player.h"

// Class created using singleton design pattern, which permits only one instance to be created
class Game {
public:
	// INITIALISATIONS
	static Game* getInstance(Player* p);
	void start(Player* p);
	void run(Game* g, Player* p);
	static std::ostream& gout();

	// MAIN

	bool save_player(Player*& p);
	void menu(Player* p);
	bool quit_game();
	void ask_to_continue();
	
	// LEVELS

	void level_selection();

	bool level_one();
	bool level_two();
	bool level_three();

private:
	static Game* instance;
	Player* p;

	Game(Player* p) : p(p) {};

	// Delete copy constructor and copy assignment operators
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
};