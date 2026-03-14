#pragma once
#include <iostream>
#include <string>
<<<<<<< HEAD
#include "player.h"

Player* menu();  //display menu to terminal 
=======
#include "Player.h"

Player* selectPlayerInstance(Player*& p);  //display menu to terminal 
>>>>>>> 1a7cf2b09a8864ec2b58283c6edb0fd63a4be372
bool load_player(Player*& player);  //used for reading in text files


