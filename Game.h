//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 14/03/26

//Changes made:
//- Add in levels functions
//- Add level two choices

#pragma once

#include "Player.h"
#include "combat.h"

// Class created using singleton design pattern, which permits only one instance to be created
class Game {
public:
	// INITIALISATIONS
	static Game* getInstance(Player* p);
	void start(Player* p);
	bool run(Game* g, Player* p);
	static std::ostream& gout();

	// MAIN
	static bool save_player(Player*& p);
	void menu(Player* p);
	static bool quit_game(Player* p);

	// LEVELS
	void level_selection(int& choice, bool& ends);

	bool level_one();
	bool level_two();
	bool level_two_choices(int choice, Combat c);
	bool level_three();
	bool end();

	// RESET GAME
	static void resetInstance();

	Player* getPlayer() { return p; };
private:
	static Game* instance;
	Player* p;

	Game(Player* p) : p(p) {};

	// Delete copy constructor and copy assignment operators
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
};