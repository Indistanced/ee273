//Author: Kyle Simpson 
//Creation Date: 07/04/26

//Changes made:
//- Add in separate player and enemy moves 
//- Make combat a struct (since we only need public variables and member functions, and struct gives us this by default)

#pragma once
#include "player.h"
#include "enemy.h"

struct Combat {
	void playerMove(Player* p, Enemy*& e); // Handles the players turn during combat
	void enemyMove(Player* p, Enemy*& e); // Handles the enemys turn during combat

	// Initializes and manages the combat cycle between the player and a newly created enemy
	bool startCombat(Player* p, std::string enemy_name, int health, int attack, std::string element);

	// Generates item drops after combat based on the defeated enemys health
	static void item_drop_generator(Player* p, int enemy_health);
};



