#pragma once
#include <vector>
#include <string>


#include "item.h"

class Player;  //player has an inventroy 

//#include "enemey.h"

class Inventory
{
public:
    bool addPotion(std::string name, std::string description, int value, int quantity); 
    bool addSpell(std::string name, std::string description, int base, int weak, int strong, std::string element);

    bool usePotion(std::string name, Player* p);
    //bool useSpell(std::string name, Enemy& enemy_name);
    void removeItem(std::string name);

    void displayItems(Player* p);
    void ask_to_continue();

    
    void addItem(const Item& item);  //for saving and loading items
    std::vector<Item>& getItems();   //for saving and loading items

private:
    std::vector<Item> inventory;
};