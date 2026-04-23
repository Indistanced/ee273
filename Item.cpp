//Author: Kyle Simpson
//Creation Date: 22/03/26

//Changes made:
//-Add in case where use point fails when player health is full

#include "Item.h"
#include "Player.h"

#include <iostream>

//───Item functions───
std::string Item::get_name() { return name; }  // Return item name
std::string Item::get_description() { return description; } // Return item description 

//───Spell functions───
int Spell::get_weak() { return weak; } // Return weak attack value
int Spell::get_strong() { return strong; } // Return strong attack value 
int Spell::get_base() { return base; } // Return base attack value 
std::string Spell::get_element() { return element; }  // Return spell elemet 

//───Potion functions───
int Potion::get_value() { return value; } // Return heath restoration value 
int Potion::get_quantity() { return quantity; } // Return number of potions 
void Potion::set_quantity(int value) { this->quantity = value; }  // Adjust number of potions 

bool Potion::use_potion(Player* p)
{
    // Ensure player dose not use potion when full health 
    if (p->getHealth() == p->getMaxHealth()) {
        std::cout << "Your health is already full.\n";
        return false;
    }
 
    // Ensure player has potion 
    if (quantity > 0) {
        p->addHealth(value);
        quantity--;  // Remove one potion 

        std::cout << "Used " << name << " (+" << value << " HP)\n";

        return true; // Potion was used successfully
    }

    return false; // Potion was not used successfully
}