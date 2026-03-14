#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>
#include <vector>

#include "Player.h"
#include "menu.h"

Player* selectPlayerInstance(Player*& p) {

    int choice;

    do {
        std::cout << "\033[3J\033[H\033[2J"; //Control sequence to clear terminal
        std::cout << "==============================\n";
        std::cout << "\tText-Based RPG\t\n";
        std::cout << "==============================\n\n";

        std::cout << "--- CHOOSE AN OPTION ---\n";
        std::cout << "1) New Game\n";
        std::cout << "2) Load Game\n";
        std::cout << "3) Quit\n";
        std::cout << "\nChoice: ";
        std::cin >> choice;

        if (choice < 1 || choice > 3 || std::cin.fail()) { // If invaild choice, clear input before re-running
            std::cout << "Invaild choice, try again.";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input stream
        }
    } while (choice < 1 || choice > 3 || std::cin.fail());

    if (choice == 3) {
        std::string exit;
        std::cout << "\033[3J\033[H\033[2J"; //Control sequence to clear terminal
        std::cout << "\n\t>> Quitting game <<\n";
        std::cout << "\nPress Enter to close...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, exit);
        return p;
    }

    else if (choice == 2) {
        if (!load_player(p)) {
            std::cout << "Save game not found.";
        }
        else {
            return p;
        }
    }
    else {
        std::string name;
        std::cout << "\033[3J\033[H\033[2J"; //Control sequence to clear terminal
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input stream
        std::cout << "Please enter your name: ";
        std::getline(std::cin, name);

        return new Player(name);  // Create a new player with a name
    }
}

bool load_player(Player*& player) {

    const std::string file_name = "game_save_file.txt"; // Constant load file path (eliminates user error)

    std::ifstream inFile(file_name);

    if (!inFile) return false; // Return false if file doesn't exist

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
    return true;
}