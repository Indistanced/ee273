//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 01/03/26

//Changes made:
//- removed attack() function as it was not needed.

#include "Character.h"

#include <string>

// Reduces the characters health by the specified damage amount
void Character::takeDamage(int dmg) {
    currentHealth -= dmg;   //update current health

    //check to ensure health dose not fall below 0
    if (currentHealth < 0) {
        currentHealth = 0;
    }
}

// Checks whether the character is still alive
bool Character::isAlive() const {
    return currentHealth > 0;
}

// Increases the characters health by a specified amount
void Character::addHealth(int health) {

    currentHealth += health; //update current health

    //Make sure health dose not exceed maximum
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}
