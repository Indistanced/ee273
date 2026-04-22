//Author: Kyle Simpson 
//Creation Date: 07/04/26

//Changes made:
//- Add in separate player and enemy moves 
//- Make combat a struct (since we only need public variables and member functions, and struct gives us this by default)

#pragma once
#include "player.h"
#include "enemy.h"

struct Combat {
	void playerMove(Player* p, Enemy*& e); // Handle the player's turn during combat
	void enemyMove(Player* p, Enemy*& e); // Handle the enemy's turn during combat

	// Initialise and manage the combat cycle between the player and a newly created enemy
	bool startCombat(Player* p, std::string enemy_name, int health, int attack, std::string element);

	// Generate item drops after combat based on the defeated enemy's health
	static void item_drop_generator(Player* p, int enemy_health);
};