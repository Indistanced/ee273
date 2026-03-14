#include <utility> // added for pair
#include <vector>

#include "inventory.h"
#include "player.h"


bool Inventory::addItem(std::string item) {

    if (item == "Bow")
    items.push_back(std::make_pair("Bow", "A long ranged attack weapon.")); // Use std::make_pair and provide both elements for the pair
}

bool Inventory::removeItem(std::string item) {

}

bool Inventory::useItem(std::string item) {

}

void displayItems() {

}