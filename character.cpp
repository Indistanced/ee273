#include "character.h"
#include <string>

Character::~Character() {
}

int Character::Attack() {
    return 0;
}

void Character::takeDamage(int dmg) {
    currentHealth -= dmg;
}

bool Character::isAlive() const{
    return currentHealth > 0;
}