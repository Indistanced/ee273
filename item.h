//Author: Kyle Simpson
//Creation Date: 22/03/26

//Changes made:
//-speratrated potions and spells into seperate classes

#pragma once
#include <string>

class Player;

class Item {
public:
    // Constructors 
    Item() : name(""), description("") {}
    Item(std::string name, std::string description) : name(name), description(description) {}

    // destructor
    virtual ~Item() {}

    //getters 
    std::string get_name();
    std::string get_description();
    
protected:
    std::string name;
    std::string description;
};

class Spell : public Item {
public:
    // Constructor 
    Spell(std::string name, std::string description, int weak, int base, int strong, std::string element) : Item(name, description), weak(weak), base(base), strong(strong), element(element) {}

    // destructor
    ~Spell() {}

    //getters
    int get_weak();
    int get_strong();
    int get_base();
    std::string get_element();

private:
    int base; // Base attack
    int weak; // Weak attack 
    int strong;  // Strong attack
    std::string element; // Element that the spell falls under
};

class Potion : public Item {
public:
    // Constructor
    Potion(std::string name, std::string description, int value, int quantity) : Item(name, description), value(value), quantity(quantity) {}

    // destructor
    ~Potion() {}

    //getters
    int get_value();
    int get_quantity();

    //setter
    void set_quantity(int value);

    //use potion function
    bool use_potion(Player* p);

private:
    int value;  // Health value
    int quantity; // Quantity 
};