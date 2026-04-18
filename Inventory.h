//Author: Kyle Simpson
//Creation Date: 22/03/26

//Changes made:
//- added in selective potion and spell getter functions
//- added in selective potion and spell display functions

#pragma once
#include <vector>
#include <string>

#include "Item.h"

class Player;  // Player has an inventory 

class Inventory {
public:
    ~Inventory();
    bool addPotion(std::string name, std::string description, int value, int quantity);
    bool addSpell(std::string name, std::string description, int base, int weak, int strong, std::string element);

    // Bool useSpell(std::string name, Enemy& enemy_name);
    void removeItem(Item* itemToRemove);

    void displayItems(Player* p);
    
    std::vector<Item*>& getItems();   // For saving and loading items
    std::vector<Potion*> getPotions(); 
    std::vector<Spell*> getSpells();

    void displaySpells();
    void displayPotions();


private:
    std::vector<Item*> inventory;
   
};