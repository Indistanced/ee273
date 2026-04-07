#pragma once
#include <vector>
#include <string>

#include "Item.h"

class Player;  //player has an inventroy 

class Inventory {
public:
    ~Inventory();
    bool addPotion(std::string name, std::string description, int value, int quantity);
    bool addSpell(std::string name, std::string description, int base, int weak, int strong, std::string element);

    //bool useSpell(std::string name, Enemy& enemy_name);
    void removeItem(Item* itemToRemove);

    void displayItems(Player* p);
    void ask_to_continue();
    
    std::vector<Item*>& getItems();   //for saving and loading items
    std::vector<Potion*> getPotions(); 
    std::vector<Spell*> getSpells();

    int getSpellNumber();
    int getPotionNumber();

    void displaySpells();
    void displayPotions();


private:
    std::vector<Item*> inventory;
   
};