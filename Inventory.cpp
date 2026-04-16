#include <vector>
#include <iostream>
#include <limits> 

#include "inventory.h"
#include "item.h"
#include "player.h"


Inventory::~Inventory() {
    for (auto item : inventory) {
        delete item;
    }
}

bool Inventory::addSpell(std::string name, std::string description, int base, int weak, int strong, std::string element) {
    inventory.push_back(new Spell(name, description, weak, base, strong, element));
    return true;
}

bool Inventory::addPotion(std::string name, std::string description, int value, int quantity) {
    for (auto& item : inventory)
    {
        if (item->get_name() == name)
        {
            Potion* p = dynamic_cast<Potion*>(item);
            if (p != nullptr) {
                p->set_quantity(p->get_quantity() + quantity);
                return true;
            }
        }
    }

    inventory.push_back(new Potion(name, description, value, quantity));
    return true;
}

void Inventory::removeItem(Item* itemToRemove) {

    for (int i = 0; i < inventory.size(); i++) {

        if (inventory[i] == itemToRemove) {

            delete inventory[i];
            inventory.erase(inventory.begin() + i);
            return;
        }
    }
}


void Inventory::displaySpells() {
    std::cout << u8"\n────────── Spell List ──────────\n";

    std::vector<Spell*> spells = getSpells();

    for (int i = 0; i < spells.size(); i++) {
        std::cout << i + 1 << ") "
            << spells[i]->get_name() << " | Type: " << spells[i]->get_element()
            << " | Power: " << spells[i]->get_base() << "\n";
    }
}

void Inventory::displayPotions() {
    std::cout << u8"\n────────── Potion List ──────────\n";

    std::vector<Potion*> potions = getPotions();

    for (int i = 0; i < potions.size(); i++) {

        std::cout << i + 1 << ") "
            << potions[i]->get_name() << " | Description: " << potions[i]->get_description()
            << " | Quantity: " << potions[i]->get_quantity() << "\n";
    }
}

void  Inventory::displayItems(Player* p) {

    while (true) {
        std::cout << "\033[3J\033[H\033[2J"; //Control sequence to clear terminal
        std::cout << u8"═════════════════════════ PLAYER INVENTORY ═════════════════════════\n";

        displaySpells();
        displayPotions();

        int choice = 0;

        std::cout << u8"\n────────── Options ──────────\n";
        std::cout << "1) Use a potion.\n";
        std::cout << "2) Exit inventory.\n";
        std::cout << "Choice: ";

        do {
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input stream
        } while (choice < 1 || choice > 2);

        if (choice == 1) {

            std::vector<Potion*> potions = getPotions();

            if (potions.empty()) {
                std::cout << "You have no potions!\n";
                ask_to_continue();
                continue;
            }

            std::cout << "\nChoose a potion: \n";
            for (int i = 0; i < potions.size(); i++) {
                std::cout << i + 1 << ") "
                    << potions[i]->get_name()
                    << " | Quantity: "
                    << potions[i]->get_quantity() << "\n";
            }

            int potionChoice;

            do {
                std::cout << "\nChoice: ";
                std::cin >> potionChoice;

            } while (potionChoice < 1 || potionChoice > potions.size());

            Potion* selectedPotion = potions[potionChoice - 1];


            if (selectedPotion->use_potion(p)) {
                std::cout << "\nYour new health is: ("
                    << p->getHealth() << "/"
                    << p->getMaxHealth() << ")\n";

                if (selectedPotion->get_quantity() == 0) {
                    removeItem(selectedPotion);
                }
            }
            else {
                std::cout << "You do not have any left.\n";
            }

            ask_to_continue();
        }

        else {
            return;
        }
    }
}


std::vector<Item*>& Inventory::getItems() {
    return inventory;
}

std::vector<Potion*> Inventory::getPotions() {
    std::vector<Potion*> potions;

    for (auto& item : inventory) {
        Potion* p = dynamic_cast<Potion*>(item);
        if (p != nullptr) {
            potions.push_back(p);
        }
    }

    return potions;
}
std::vector<Spell*> Inventory::getSpells() {
    std::vector<Spell*> spells;

    for (auto& item : inventory) {
        Spell* s = dynamic_cast<Spell*>(item);
        if (s != nullptr) {
            spells.push_back(s);
        }
    }

    return spells;
}


void Inventory::ask_to_continue() {
    std::string input;

    std::cout << "\n>> Press enter to continue <<";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //claer input stream
    std::getline(std::cin, input); //return when enter is recived.
    return;
}

int Inventory::getSpellNumber() {
    int count = 0;
    for (auto& item : inventory) {
        Spell* s = dynamic_cast<Spell*>(item);
        if (s != nullptr) {
            count++;
        }
    }

    return count;

}
int Inventory::getPotionNumber() {
    int count = 0;
    for (auto& item : inventory) {
        Potion* p = dynamic_cast<Potion*>(item);
        if (p != nullptr) {
            count++;
        }
    }

    return count;
}