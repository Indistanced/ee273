#pragma once
#include <vector>
#include <string>


#include "Item.h"

class Player;  //player has an inventroy 

//#include "enemey.h"

class Inventory {
public:
    ~Inventory();
    bool addPotion(std::string name, std::string description, int value, int quantity);
    bool addSpell(std::string name, std::string description, int base, int weak, int strong, std::string element);

    //bool useSpell(std::string name, Enemy& enemy_name);
    void removeItem(std::string name);

    void displayItems(Player* p);
    void ask_to_continue();
    
    std::vector<Item*>& getItems();   //for saving and loading items

private:
    std::vector<Item*> inventory;
   
};