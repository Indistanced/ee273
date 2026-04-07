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
    std::string title = "Text-Based RPG";

    do {
        terminateBuffer();
        enbox(title);

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
        std::cout << "\n>> Quitting game <<\n";
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

        p = new Player(name);
        int choice;

        Game::gout() << "Welcome, " << name << "!\n";
        Game::gout() << u8"You awaken in a town and are faced with a choice of spells—which will you choose?\n";
        xbar();
        std::cout << u8"\n── CHOOSE A SPELL ──\n";
        std::cout << "1. Fireball\n";
        std::cout << "2. Ice Spike\n";
        std::cout << "3. Lightning Strike\n";
        xbar(); std::cout << '\n';
        do {
            Player::pin(p) >> choice;
            if (choice < 1 || choice > 3) {
                Game::gout() << "Choice out of range. Try again.\n";
            }
        } while (choice < 1 || choice > 3);

        // Add spell to player inventory
        switch (choice) {
        case 1: p->getInventory().addSpell("Fireball", "Strong against leaf", 20, 10, 30, "Fire");
            break;
        case 2: p->getInventory().addSpell("Ice Spike", "Strong against fire", 15, 12, 20, "Water");
            break;
        case 3: p->getInventory().addSpell("Leaf slash", "Strong againt water", 25, 5, 35, "Leaf");
            break;
        default: Game::gout() << "A horrific error has occurred.";
            break;
        }

        xbar(); std::cout << '\n';
        Game::gout() << "Ahh, a fine choice!\n";
        Game::gout() << u8"Your adventure will be dangerous──so take this.\n";
        std::cout << u8"── You received a health potion worth +25 HP! ──\n";
        p->getInventory().addPotion("Health Potion", "Restores +25 HP", 25, 1); // Add health potion to inventory.

        std::string input;

        std::cout << "\n>> Press enter to continue <<";
        clearBuffer();
        std::getline(std::cin, input); // Return when new line (enter is recived)
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
        } else if (type == "spell") {
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
        } else {
            player->addQuest(description, false);
        }
    }

    return true;
}