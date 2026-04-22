//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 08/03/26

//Changes made:
//- Add in player choice function
//- Add game over functionality

#pragma once
#include <iostream>
#include <string>
#include "Player.h"
#include "unicode.h"

Player* selectPlayerInstance(Player*& p);  // Display menu to terminal 
bool load_player(Player*& player);  // Used for reading in text files
void playerInstanceOptions(int& choice, std::string one, std::string two = "INVALID", std::string three = "INVALID", std::string header_text = "CHOOSE AN OPTION"); // Select a choice
bool gameOverMenu(Player* p);  // Display game over when player is defeated in combat 