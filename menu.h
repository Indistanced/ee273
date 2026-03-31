#pragma once
#include <iostream>
#include <string>
#include "Player.h"
#include "unicode.h"

Player* selectPlayerInstance(Player*& p);  //display menu to terminal 
bool load_player(Player*& player);  //used for reading in text files