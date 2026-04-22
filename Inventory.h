//Author: Kyle Simpson
//Creation Date: 22/03/26

//Changes made:
//- Add in separate potion and spell getter functions
//- Add in separate potion and spell display functions

#pragma once
#include <vector>
#include <string>

#include "Item.h"

class Player;  // Forward declaration of Player for composition relationship 

class Inventory {
public:
    ~Inventory(); // Destructor - ensures all dynamically allocated items are deallocated

    // Add item functions
    bool addPotion(std::string name, std::string description, int value, int quantity);
    bool addSpell(std::string name, std::string description, int base, int weak, int strong, std::string element);

    void removeItem(Item* itemToRemove); // Remove item from inventory using name of item

    std::vector<Item*>& getItems();   // For saving and loading items
    std::vector<Potion*> getPotions(); // Return all potions 
    std::vector<Spell*> getSpells(); // Return all spells

    // Display functions
    void displaySpells();
    void displayPotions();
    void displayItems(Player* p);

private:
    std::vector<Item*> inventory; // Store all items as pointers to the base Item class
};