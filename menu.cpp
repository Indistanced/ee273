//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 08/03/26

//Changes made:
//- updated story telling text
//- updated load function with location
//- updated load fucntion with level and experince
//- updated load function with inventory and quest

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>
#include <vector>
#include <sstream>

#include "Player.h"
#include "menu.h"
#include "Game.h"
#include "clear.h"
#include "Game_Level.h"
#include "Minimap.h"
#include "main.h"

#include <Windows.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

void playerInstanceOptions(int& choice, std::string one, std::string two, std::string three, std::string header_text) {
    std::cout << "─── " << header_text << " ───\n";
    std::cout << "1) " << one << "\n";
    if (two != "INVALID") {
        std::cout << "2) " << two << "\n";
        if (three != "INVALID") {
            std::cout << "3) " << three << "\n";
        }
    } std::cout << "\nChoice: ";
    std::cin >> choice;
}

Player* selectPlayerInstance(Player*& p) {
    int choice;
    std::string title = "Spells and Potions RPG";

    do {
        terminateBuffer();
        enbox(title); std::cout << '\n';

        playerInstanceOptions(choice, "New Game", "Load Game", "Quit", "Choose an Option");
        if (choice < 1 || choice > 3 || std::cin.fail()) { // If invalid choice, clear input before re-running
            clearBuffer(); terminateBuffer();
        }

    } while (choice < 1 || choice > 3 || std::cin.fail());

    if (choice == 3) {
        terminateBuffer();
        std::cout << "\n>> Quitting game <<\n";
        std::cout << "\nPress Enter to close...";
        running = false;
        clearBuffer();
        std::cin.get();
        return p;
    }
    else if (choice == 2) {
        if (!load_player(p)) {

            std::cout << "Save game not found.\n";
            std::cout << "Press enter to continue...";
            std::cin.ignore();
            std::cin.get();

            return selectPlayerInstance(p);
        }
        else return p;
    }
    else {
        std::string name;
        terminateBuffer();
        clearBuffer();
        std::cout << "\n>> Please enter your name: ";
        std::getline(std::cin, name);

        p = new Player(name);
        int choice;

        Game::gout() << "Welcome, " << name << "!\n";
        Game::gout() << "You awaken in the town square.\n";

        Game::gout() << "You are surrounded by a crowd of terrified people.\n";
        Game::gout() << "For weeks creatures have been appering from a dark place...\n";
        Game::gout() << "A place known as the Arm of Dismay.\n";
        Game::gout() << "They emerging and attacking anything in their path!\n\n";

        Game::gout() << "If nothing is done the town will fall...\n";
        Game::gout() << "The knights have tried and failed.\n";
        Game::gout() << "Now, all eyes turn to you (a beginner but powerful mage).\n\n";

        Game::gout() << "You must enter the Arm of Dismay and put an end to whatever lies within.\n";
        Game::gout() << "You are the towns only hope!\n\n";

        Game::gout() << "Before you set out, you must choose a spell to aid you.\n";
        xbar(); std::cout << "\n";


        while(true) {


            playerInstanceOptions(choice, "Fire Spin", "Water Whip", "Lead Slash", "CHOOSE A SPELL");

            // Add spell to player inventory.
            if (choice == 1)
            {
                p->getInventory().addSpell("Fire Spin", "Weak fire ability", 16, 10, 24, "fire");
                break;
            }
            else if (choice == 2)
            {
                p->getInventory().addSpell("Water Whip", "Weak water ability", 15, 12, 25, "water");
                break;
            }
            else if (choice == 3)
            {
                p->getInventory().addSpell("Leaf Slash", "Weak grass ability", 14, 8, 26, "grass");
                break;
            }
            else {
                std::cout << "Invaild choice, try again.\n\n";
                clearBuffer();
            }
        }

        xbar(); std::cout << "\n";
        Game::gout() << "Ahh, a fine choice!\n";

        Game::gout() << "Your first quest is to defeat a slime\n";
        p->addQuest("Defeat a slime", false);

        Game::gout() << "Prove your strength then venture to through the Green Hills!\n\n";
        std::cout << "Villager: Your adventure will be difficult here, take this.\n";

        std::cout << "───── You receive a +25 health potion ─────\n";
        p->getInventory().addPotion("Small Health Potion", "Restores +25 HP", 25, 1); // Add health potion to inventory.

        ask_to_continue();
        return p;  // Create a new player with a name
    }
}

bool gameOverMenu(Player* p) {
    int choice;

    /*Game* g = Game::getInstance(Player::p);

    Player* p = g->getPlayer();*/

    do {
        terminateBuffer();

        std::cout << "──── FINAL STATS ────\n";
        p->to_string(); std::cout << "\n";

        playerInstanceOptions(choice, "Restart Game", "Quit", "INVALID", "GAME OVER!");
        if (choice < 1 || choice > 3 || std::cin.fail()) { // If invalid choice, clear input before re-running
            clearBuffer(); terminateBuffer();
        }

    } while (choice != 1 && choice != 2);

    return (choice == 1);
}

bool load_player(Player*& player) {

    const std::string file_name = "game_save_file.txt"; // Constant load file path (eliminates user error)

    std::ifstream inFile(file_name);

    if (!inFile) { return false; } // Return false if file doesn't exist

    std::string name, location;
    int hp, maxHp, strength, level, exp, expLim;

    std::getline(inFile, name);
    inFile >> hp;
    inFile >> maxHp;
    inFile >> level;
    inFile >> exp;
    inFile >> expLim;
    inFile >> strength;
    inFile.ignore();
    std::getline(inFile, location);

    player = new Player(name, hp, maxHp, strength, location, level, exp, expLim);

    int itemCount;
    inFile >> itemCount;
    inFile.ignore();


    for (int i = 0; i < itemCount; i++)
    {
        std::string line;
        std::getline(inFile, line);

        std::stringstream ss(line);
        std::string type;

        std::getline(ss, type, ',');

        if (type == "potion") {
            std::string name, desc, temp;
            int value, quantity;

            std::getline(ss, name, ',');
            std::getline(ss, desc, ',');

            std::getline(ss, temp, ',');
            value = std::stoi(temp);

            std::getline(ss, temp, ',');
            quantity = std::stoi(temp);

            player->getInventory().addPotion(name, desc, value, quantity);
        }
        else if (type == "spell") {
            std::string name, desc, element, temp;
            int base, weak, strong;

            std::getline(ss, name, ',');
            std::getline(ss, desc, ',');

            std::getline(ss, temp, ',');
            base = std::stoi(temp);

            std::getline(ss, temp, ',');
            weak = std::stoi(temp);

            std::getline(ss, temp, ',');
            strong = std::stoi(temp);

            std::getline(ss, element, ',');

            player->getInventory().addSpell(name, desc, base, weak, strong, element);
        }
    }

    int questCount;
    inFile >> questCount;
    inFile.ignore();

    for (int i = 0; i < questCount; i++)
    {
        std::string line;
        std::getline(inFile, line);

        std::stringstream ss(line);
        std::string description;
        std::string status;

        std::getline(ss, description, '|');
        std::getline(ss, status, '|');

        if (status == "Complete") {
            player->addQuest(description, true);
        }
        else {
            player->addQuest(description, false);
        }
    }

    return true;
}