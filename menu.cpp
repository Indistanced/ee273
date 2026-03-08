#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>

#include "player.h"
#include "menu.h"

Player* menu() {
    int choice;

    std::cout << "#####################\n";
    std::cout << "   Text-Based RBG   \n";
    std::cout << "#####################\n";

    do {
        std::cout << "\n1) New Game\n";
        std::cout << "2) Load Game\n";
        std::cout << "3) Quit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice < 1 || choice > 3) {   //If invaild choice clear input before re-running
            std::cout << "Invaild choice, try again.";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear input stream
        }
    } while (choice < 1 || choice > 3);


    Player* player = nullptr;  //initialisation of player

    if (choice == 3) {
        return player;
    }

    else if (choice == 2) {
        if (!load_player(player)) {
            std::cout << "Save game not found.";
        }
        else {
            return player;
        }
    }

    else {
        std::string name;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear input stream
        std::cout << "Please enter your name: ";
        std::getline(std::cin, name);

        return new Player(name);  //create a new player with a name
    }
}

bool load_player(Player*& player) {

    const std::string file_name = "game_save_flie.txt"; //constant load file path (eliminates user error)

    std::ifstream inFile(file_name);

    if (!inFile) {
        return false;
    }

    std::string name, location;
    int hp, maxHp, strength;
    
    std::getline(inFile, name);
    inFile >> hp;
    inFile >> maxHp;
    inFile >> strength;

    inFile.ignore();
    std::getline(inFile, location);

    player = new Player(name, hp, maxHp, strength, location);
    return true;
}