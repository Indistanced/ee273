//Author: Kyle Simpson
//Creation Date: 22/03/26


#include "Item.h"
#include "Player.h"

#include <iostream>

//----Item functions---
std::string Item::get_name() { return name; }  // return item name
std::string Item::get_description() { return description; } //return item description 

//---Spell functions---
int Spell::get_weak() { return weak; } //return weak attack value
int Spell::get_strong() { return strong; } //return strong attack value 
int Spell::get_base() { return base; } //return base attack value 
std::string Spell::get_element() { return element; }  //return spell elemet 

//---Potion functions---
int Potion::get_value() { return value; } //return heath restoration value 
int Potion::get_quantity() { return quantity; } //return number of potions 
void Potion::set_quantity(int value) { this->quantity = value; }  //adjust number of potions 



bool Potion::use_potion(Player* p)
{
    //check to ensure player dose not use potion when full health 
    if (p->getHealth() == p->getMaxHealth()) {
        std::cout << "Your health is alreay full.\n";
        return false;
    }
 
    //check to ensure player has potion 
    if (quantity > 0) {
        p->addHealth(value);
        quantity--;  //remove one potion 

        std::cout << "Used " << name << " (+" << value << " HP)\n";

        return true; //potion was used successfully
    }

    return false; //potion is not used successfully
}