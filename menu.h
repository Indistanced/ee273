//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 08/03/26

//Changes made:
//- added in player choice function
//- added game over functionality

#pragma once
#include <iostream>
#include <string>
#include "Player.h"
#include "unicode.h"

Player* selectPlayerInstance(Player*& p);  // Display menu to terminal 
bool load_player(Player*& player);  // Used for reading in text files
void playerInstanceOptions(int& choice, std::string one, std::string two = " ", std::string three = " "); // Select a choice
bool gameOverMenu();