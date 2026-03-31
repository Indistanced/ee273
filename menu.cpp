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

Player* selectPlayerInstance(Player*& p) {
    int choice;

    do {
        std::string title = "Text-Based RPG";

        terminateBuffer();
        enbox(title);
        enbox("HELLLLLO WORLD!");

        std::cout << u8"─── CHOOSE AN OPTION ───\n";
        std::cout << "1) New Game\n";
        std::cout << "2) Load Game\n";
        std::cout << "3) Quit\n";
        std::cout << "\nChoice: ";
        std::cin >> choice;

        if (choice < 1 || choice > 3 || std::cin.fail()) { // If invaild choice, clear input before re-running
            std::cout << "Invaild choice, try again.";
            clearBuffer();
        }
    } while (choice < 1 || choice > 3 || std::cin.fail());

    if (choice == 3) {
        std::string exit;
        terminateBuffer();
        std::cout << "\n\t>> Quitting game <<\n";
        std::cout << "\nPress Enter to close...";
        clearBuffer();
        std::getline(std::cin, exit);
        return p;
    } else if (choice == 2) {
        if (!load_player(p)) {
            std::cout << "Save game not found.";
        } else {
            return p;
        }
    } else {
        std::string name;
        terminateBuffer();
        clearBuffer();
        std::cout << "Please enter your name: ";
        std::getline(std::cin, name);

        Player* p = new Player(name);
        int choice;

        Game::gout() << "Welcome, " << name << "!\n";
        Game::gout() << "You awaken in a town and are faced with a choice of spells—which will you choose? \n";
        xbar(12);
        std::cout << "\n-- CHOOSE A SPELL --\n";
        std::cout << "1. Fireball\n";
        std::cout << "2. Ice Spike\n";
        std::cout << "3. Lightning Strike\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 1)  // Add spell to player inventory.
        {
            p->getInventory().addSpell("Fireball", "Strong against water", 20, 10, 30, "Fire");
        }
        else if (choice == 2)
        {
            p->getInventory().addSpell("Ice Spike", "Strong against fire", 15, 12, 20, "Ice");
        }
        else if (choice == 3)
        {
            p->getInventory().addSpell("Lightning", "Strong againt earth", 25, 5, 35, "Electric");
        }

        std::cout << "\nAh a fine choice!\n";
        std::cout << "\nYour adventure will be long here take this.\n";
        std::cout << "-- You recive a +25 health potion --\n";
        p->getInventory().addPotion("Health Potion", "Restores +25 HP", 25, 1); //adds health potion to inventory.

        std::string input;

        std::cout << "\n>> Press enter to continue <<";
        clearBuffer();
        std::getline(std::cin, input); //return when new line (enter is recived)
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

        Item item;

        std::stringstream ss(line);
        std::string temp;

        std::getline(ss, item.name, ',');
        std::getline(ss, item.description, ',');
        std::getline(ss, item.type, ',');

        std::getline(ss, temp, ',');
        item.value = std::stoi(temp);

        std::getline(ss, temp, ',');
        item.quantity = std::stoi(temp);

        std::getline(ss, temp, ',');
        item.weak = std::stoi(temp);

        std::getline(ss, temp, ',');
        item.strong = std::stoi(temp);

        std::getline(ss, item.element, ',');

        player->getInventory().addItem(item);
    }

    return true;
}