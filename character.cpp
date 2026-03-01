#include "character.h"
#include <string>


Character::Character(std::string Name) {
    name = Name;
    health = 100;
    maxHealth = 100;
}
Character::Character(std::string Name, int hp) {
    name = Name;
    health = hp;
    maxHealth = hp;
}
Character::~Character() {
}

int Character::Attack() {
    return 0;
}

void Character::takeDamage(int dmg) {
    health = health - dmg;
}

bool Character::isAlive() const{
    return health > 0;
}

std::string Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}