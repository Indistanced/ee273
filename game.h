#pragma once

#include "Player.h"

// Class created using singleton design pattern, which permits only one instance to be created
class Game {
public:
	static Game* getInstance(Player* p);
	void start(Player* p);
	bool save_player(Player*& p);
	void run(Game* g, Player* p);
	static std::ostream& gout();

    void Player_Menu(Player* p);
    bool quit_game();

private:
	static Game* instance;
	Player* p;

	Game(Player* p) : p(p) {};

	// Delete copy constructor and copy assignment operators
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
};