//Author:  Kyle Simpson and Aidan Kelly
//Creation Date: 07/04/26

//Changes made:
//- added in seperate player and enemy moves 
//- made comabt a struct 

#pragma once
#include "player.h"
#include "enemy.h"

struct Combat {
	void playerMove(Player* p, Enemy*& e);
	void enemyMove(Player* p, Enemy*& e);

	bool startCombat(Player* p, std::string enemy_name, int health, int attack, std::string element);
	void item_drop_generator(Player* p, int enemy_health);
};



