#pragma once
#include <iostream>
#include <string>
#include "Player.h"
#include "unicode.h"

Player* selectPlayerInstance(Player*& p);  // Display menu to terminal 
bool load_player(Player*& player);  // Used for reading in text files
void playerInstanceOptions(int& choice, std::string one, std::string two = " ", std::string three = " "); // Select a choice