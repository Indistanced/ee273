#pragma once
#include <string>

struct Item
{
    std::string name;
    std::string description;

    std::string type; // potion or spell

    int value;      // heal or base attack
    int quantity;   // used for potion number

    // spell data
    int weak; //weak attack 
    int strong;  // strong attack
    std::string element; // element that spell fall under
};