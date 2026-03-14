#include "Character.h"
<<<<<<< HEAD:character.cpp
#include <string>

=======

#include <string>

>>>>>>> 1a7cf2b09a8864ec2b58283c6edb0fd63a4be372:Character.cpp
int Character::Attack() {
    return 0;
}

void Character::takeDamage(int dmg) {
    currentHealth -= dmg;
}

bool Character::isAlive() const {
    return currentHealth > 0;
}