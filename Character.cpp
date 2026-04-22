//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 01/03/26

//Changes made:
//- Remove attack() function as it was not needed
//- Refine take damage validation to ensure health did not drop below 0

#include "Character.h"

#include <string>

// Reduce the character's health by the specified damage amount
void Character::takeDamage(int dmg) {
    currentHealth -= dmg;   // Update current health

    // Ensure health does not fall below 0
    if (currentHealth < 0) {
        currentHealth = 0;
    }
}

// Check whether the character is still alive
bool Character::isAlive() const {
    return currentHealth > 0;
}

// Increase the character's health by a specified amount
void Character::addHealth(int health) {

    currentHealth += health; // Update current health

    // Ensure health does not exceed maximum
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}