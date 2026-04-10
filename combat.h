#pragma once
#include "player.h"
#include "enemy.h"

struct Combat {
	void playerMove(Player* p, Enemy& e);
	void enemyMove(Player* p, Enemy& e);

	bool startCombat(Player* p, std::string enemy_name, int health, int attack, std::string element);
	void item_drop_generator(Player* p, int enemy_health);
};



