#include "Character.h"

#include <string>

void Character::takeDamage(int dmg) {
    currentHealth -= dmg;

    if (currentHealth < 0) {
        currentHealth = 0;
    }
}

bool Character::isAlive() const {
    return currentHealth > 0;
}

void Character::addHealth(int health) {

    currentHealth += health;

    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}
