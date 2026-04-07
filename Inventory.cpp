#include <vector>
#include <iostream>
#include <limits> 

#include "Inventory.h"
#include "Item.h"
#include "Player.h"


Inventory::~Inventory() {
    for (auto item : inventory) {
        delete item;
    }
}

bool Inventory::addSpell(std::string name, std::string description,
    int base, int weak, int strong, std::string element)
{
    for (auto& items : inventory) {
        if (items->get_name() == name) {
            removeItem(name);
        }
    }
    inventory.push_back(new Spell(name,description, weak, base, strong, element));
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

void Inventory::removeItem(std::string name) {
    for (int i = 0; i < inventory.size(); i++)
    {
        if (inventory[i]->get_name() == name)
        {
            delete inventory[i];
            inventory.erase(inventory.begin() + i);
        }
    }
}


void  Inventory::displayItems(Player* p) {

    while (true) {
        std::cout << "\033[3J\033[H\033[2J"; //Control sequence to clear terminal
        std::cout << "\n======================== PLAYER INVENTORY ========================\n";
        std::cout << "\n---- Spell List --------------\n";

        for (auto& item : inventory) {
            Spell* s = dynamic_cast<Spell*>(item);
            if (s != nullptr) {
                std::cout << item->get_name() << " | Description: " << item->get_description() << " | Type: " << s->get_element() << " | Power: " << s->get_base() << "\n";
            }
        }

        std::cout << "\n---- Potion List --------------\n";

        for (auto& item : inventory) {
            Potion* p = dynamic_cast<Potion*>(item);
            if (p != nullptr) {
                std::cout << item->get_name() << " | Description: " << item->get_description() << " | Quantity: " << p->get_quantity() << "\n";
            }
        }

        int choice = 0;

        std::cout << "\n\n---- Options --------------\n";
        std::cout << "1) Use a potion.\n";
        //std::cout << "2) Use a spell.\n";
        std::cout << "2) Exit inventory.\n";
        std::cout << "Choice: ";

        do {
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input stream
        } while (choice < 1 || choice > 2);

        if (choice == 1) {
            std::string name;
            std::cout << "What potion would you like to use" << std::endl;
            std::getline(std::cin, name);

            for (auto& item : inventory) {
                if (item->get_name() == name) {
                    Potion* po = dynamic_cast<Potion*>(item);
                    if (po != nullptr) {
                        if (po->use_potion(p)) {
                            std::cout << "\nYour new health is: (" << p->getHealth() << "/" << p->getMaxHealth() << ")\n";
                            ask_to_continue();
                        }
                        else {
                            std::cout << "You do not own this potion.\n";
                            ask_to_continue();
                        }

                    }
                }
            }
        }

        else if (choice == 2) {
            return;
        }
    }
}


std::vector<Item*>& Inventory::getItems() {
    return inventory;
}


void Inventory::ask_to_continue() {
    std::string input;

    std::cout << "\n>> Press enter to continue <<";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //claer input stream
    std::getline(std::cin, input); //return when enter is recived.
    return;
}