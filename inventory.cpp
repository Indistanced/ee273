#include <vector>
#include <iostream>
#include <limits> 

#include "inventory.h"
#include "item.h"
#include "player.h"


bool Inventory::addSpell(std::string name, std::string description,
    int base, int weak, int strong, std::string element)
{
    Item item;
    item.name = name;
    item.description = description;
    item.type = "spell";

    item.value = base;
    item.weak = weak;
    item.strong = strong;
    item.element = element;

    inventory.push_back(item);
    return true;
}

bool Inventory::addPotion(std::string name, std::string description, int value, int quantity)
{
    for (auto& item : inventory)
    {
        if (item.name == name && item.type == "potion")
        {
            item.quantity += quantity;
            return true;
        }
    }

    Item item;
    item.name = name;
    item.description = description;
    item.type = "potion";
    item.value = value;
    item.quantity = quantity;

    inventory.push_back(item);
    return true;
}

void Inventory::removeItem(std::string name)
{
    for (int i = 0; i < inventory.size(); i++)
    {
        if (inventory[i].name == name)
        {
            inventory.erase(inventory.begin() + i);
        }
    }
}

bool Inventory::usePotion(std::string name, Player* p)
{
    for (auto& item : inventory)
    {
        if (item.name == name && item.type == "potion")
        {
            if (item.quantity > 0)
            {
                p->addHealth(item.value);
                item.quantity--;

                std::cout << "Used " << item.name << " (+"
                    << item.value << " HP)\n";

                if (item.quantity == 0) {
                    removeItem(name);
                }

                return true;
            }
        }
    }

    return false;
}

void  Inventory::displayItems(Player* p) {

    while (true) {
        std::cout << "\033[3J\033[H\033[2J"; //Control sequence to clear terminal
        std::cout << "\n======================== PLAYER INVENTORY ========================\n";
        std::cout << "\n---- Spell List --------------\n";

        for (auto& item : inventory) {
            if (item.type == "spell") {
                std::cout << item.name << " | Description: " << item.description << " | Type: " << item.element << " | Power: " << item.value << "\n";
            }
        }

        std::cout << "\n---- Potion List --------------\n";

        for (auto& item : inventory) {
            if (item.type == "potion") {
                std::cout << item.name << " | Description: " << item.description << " | Quantity: " << item.quantity << "\n";
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
            if (p->getInventory().usePotion(name, p)) {
                std::cout << "\nYour new health is: (" << p->getHealth() << "/" << p->getMaxHealth() << ")\n";
                ask_to_continue();
            }
            else {
                std::cout << "You do not own this potion.\n";
                ask_to_continue();
            }
        }
        else if (choice == 2) {
            return;
        }
    }
}

void Inventory::addItem(const Item& item) {
    inventory.push_back(item);
}

std::vector<Item>& Inventory::getItems() {
    return inventory;
}

void Inventory::ask_to_continue() {
    std::string input;

    std::cout << "\n>> Press enter to continue <<";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //claer input stream
    std::getline(std::cin, input); //return when enter is recived.
    return;
}