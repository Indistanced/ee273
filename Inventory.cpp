//Author: Kyle Simpson
//Creation Date: 22/03/26

//Changes made:
//- Add in dynamic casting of potions and spells
//- Add in unicode to text
//- Add in separate potion and spell getter functions
//- Add in separate potion and spell display functions

#include <vector>
#include <iostream>
#include <limits> 

#include "inventory.h"
#include "item.h"
#include "player.h"
#include "clear.h"

// Destructor - frees all dynamically allocated items in the inventory
Inventory::~Inventory() {
    for (auto item : inventory) {
        delete item;
    }
}

// Adds a new spell to the inventory
bool Inventory::addSpell(std::string name, std::string description, int base, int weak, int strong, std::string element) {
    inventory.push_back(new Spell(name, description, weak, base, strong, element));
    return true;
}

// Adds a potion to the inventory
// If the potion already exists its quantity is increased instead of adding a duplicate
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

    // If potion does not exist create and add a new one
    inventory.push_back(new Potion(name, description, value, quantity));
    return true;
}

// Removes a specific item from the inventory
void Inventory::removeItem(Item* itemToRemove) {

    for (int i = 0; i < inventory.size(); i++) {

        if (inventory[i] == itemToRemove) {

            delete inventory[i]; // Free memory
            inventory.erase(inventory.begin() + i);
            return;
        }
    }
}


// Displays all spells currently in the players inventory
void Inventory::displaySpells() {
    std::cout << "\n──────────────── Spell List ────────────────\n";

    std::vector<Spell*> spells = getSpells(); //get all spells

    for (int i = 0; i < spells.size(); i++) {
        std::cout << i + 1 << ") "
            << spells[i]->get_name() << " | Type: " << spells[i]->get_element()
            << " | Power: " << spells[i]->get_base() << "\n";
    }
}

// Displays all potions currently in the players inventory
void Inventory::displayPotions() {
    std::cout << "\n──────────────── Potion List ────────────────\n";

    std::vector<Potion*> potions = getPotions(); // Get all potions 

    for (int i = 0; i < potions.size(); i++) {

        std::cout << i + 1 << ") "
            << potions[i]->get_name() << " | Description: " << potions[i]->get_description()
            << " | Quantity: " << potions[i]->get_quantity() << "\n";
    }
}

// Allows the player to view items, use potions or exit the inventory
void  Inventory::displayItems(Player* p) {

    while (true) {
        terminateBuffer();
        std::cout << "═════════════════════════ PLAYER INVENTORY ═════════════════════════\n";

        displaySpells();
        displayPotions();

        int choice = 0;

        std::cout << "\n────────── Options ──────────\n";
        std::cout << "1) Use a potion.\n";
        std::cout << "2) Exit inventory.\n";
        std::cout << "Choice: ";

        // Input validation loop
        do {
            std::cin >> choice;
            clearBuffer();
        } while (choice < 1 || choice > 2);

        if (choice == 1) {

            std::vector<Potion*> potions = getPotions();

            // Handle case where no potions exist
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

            // Input loop for user selecting a valid potion 
            do {
                std::cout << "\nChoice: ";
                std::cin >> potionChoice;
                clearBuffer();

            } while (potionChoice < 1 || potionChoice > potions.size());

            Potion* selectedPotion = potions[potionChoice - 1];


            // Attempt to use the selected potion
            if (selectedPotion->use_potion(p)) {
                std::cout << "\nYour new health is: ("
                    << p->getHealth() << "/"
                    << p->getMaxHealth() << ")\n";

                //remove item if quantity reaches zero
                if (selectedPotion->get_quantity() == 0) {
                    removeItem(selectedPotion);
                }
            }


            ask_to_continue();
        }

        else {
            return; // Exit inventory
        }
    }
}


// Return reference to full inventory (used for saving and loading functionality)
std::vector<Item*>& Inventory::getItems() {
    return inventory;
}

// Return a filtered list of Potions only 
std::vector<Potion*> Inventory::getPotions() {
    std::vector<Potion*> potions;

    for (auto& item : inventory) {
        Potion* p = dynamic_cast<Potion*>(item); // Use dynamic_cast to identify correct type
        if (p != nullptr) {
            potions.push_back(p);
        }
    }

    return potions;
}

// Return a filtered list of Spells only 
std::vector<Spell*> Inventory::getSpells() {
    std::vector<Spell*> spells;

    for (auto& item : inventory) {
        Spell* s = dynamic_cast<Spell*>(item); // Use dynamic_cast to identify correct type
        if (s != nullptr) {
            spells.push_back(s);
        }
    }

    return spells;
}
