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

Player* selectPlayerInstance(Player*& p) {
    int choice;
    std::string title = "Spells and Potions RPG";

    do {
        terminateBuffer();
        enbox(title); std::cout << '\n';

        Level::test();

        std::cout << "─── CHOOSE AN OPTION ───\n";
        std::cout << "1) New Game\n";
        std::cout << "2) Load Game\n";
        std::cout << "3) Quit\n";
        std::cout << "\nChoice: ";
        std::cin >> choice;

        if (choice < 1 || choice > 3 || std::cin.fail()) { // If invaild choice, clear input before re-running
            clearBuffer(); terminateBuffer();
        }

    } while (choice < 1 || choice > 3 || std::cin.fail());

    if (choice == 3) {
        terminateBuffer();
        std::cout << "\n>> Quitting game <<\n";
        std::cout << "\nPress Enter to close...";
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
        else {
            return p;
        }
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
        Game::gout() << "You awaken in a town and are faced with a choice of spells, which will you choose?\n";
        xbar();
        std::cout << "\n── CHOOSE A SPELL ──\n";
        std::cout << "1. Fire Spin\n";
        std::cout << "2. Water Whip\n";
        std::cout << "3. Leaf Slash\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 1)  // Add spell to player inventory.
        {
            p->getInventory().addSpell("Fire Spin", "Weak fire ability", 20, 10, 24, "fire");
        }
        else if (choice == 2)
        {
            p->getInventory().addSpell("Water Whip", "Weak water ability", 15, 12, 25, "water");
        }
        else if (choice == 3)
        {
            p->getInventory().addSpell("Leaf Slash", "Weak grass ability", 15, 5, 28, "grass");
        }

        xbar();
        std::cout << "\n>> Ahh, a fine choice!\n";

        std::cout << "\n>> Your first quest is to defeat a slime\n";
        p->addQuest("Defeat a slime", false);

        std::cout << "\n>> Your adventure will be difficult──here, take this.\n";
        std::cout << "───── You receive a +25 health potion ─────\n";
        p->getInventory().addPotion("Small Health Potion", "Restores +25 HP", 25, 1); // Add health potion to inventory.

        ask_to_continue();
        return p;  // Create a new player with a name
    }
}

bool load_player(Player*& player) {

    const std::string file_name = "game_save_file.txt"; // Constant load file path (eliminates user error)

    std::ifstream inFile(file_name);

    if (!inFile) { return false; } // Return false if file doesn't exist

    std::string name, location;
    int hp, maxHp, strength, level, exp;

    std::getline(inFile, name);
    inFile >> hp;
    inFile >> maxHp;
    inFile >> level;
    inFile >> exp;
    inFile >> strength;
    inFile.ignore();
    std::getline(inFile, location);

    player = new Player(name, hp, maxHp, strength, location, level, exp);

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