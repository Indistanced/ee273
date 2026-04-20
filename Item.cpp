//Author: Kyle Simpson
//Creation Date: 22/03/26


#include "Item.h"
#include "Player.h"

#include <iostream>


std::string Item::get_name() { return name; }
std::string Item::get_description() { return description; }

int Spell::get_weak() { return weak; }
int Spell::get_strong() { return strong; }
int Spell::get_base() { return base; }
std::string Spell::get_element() { return element; }

int Potion::get_value() { return value; }
int Potion::get_quantity() { return quantity; }
void Potion::set_quantity(int value) { this->quantity = value; }


bool Potion::use_potion(Player* p)
{

    if (p->getHealth() == p->getMaxHealth()) {
        std::cout << "Your health is alreay full.\n";
        return false;
    }
 
    if (quantity > 0) {
        p->addHealth(value);
        quantity--;

        std::cout << "Used " << name << " (+" << value << " HP)\n";

        return true;
    }

    return false;
}