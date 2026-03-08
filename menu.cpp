#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include "menu.h"

void menu() {

    int choice;
    
    std::cout << "####################";
    std::cout << "   Text-Based RBG   ";
    std::cout << "####################";

    do {
        std::cout << "1) New Game\n";
        std::cout << "2) Load Game\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if(std::cin.fail() || choice != 1 || choice != 2) {
            std::cout << "Invaild choice, try again.";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max());
        }
    }while (choice != 1 || choice != 2);

    std::cout << choice;



}