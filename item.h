#pragma once
#include <string>

class Player;

class Item {
public: 
    // Add a default constructor to fix E0291
    Item() : name(""), description("") {}
    Item(std::string name, std::string description) : name(name), description(description) {}
    virtual ~Item() {}

    std::string get_name();
    std::string get_description();
protected:
    std::string name;
    std::string description;
};

class Spell : public Item {
public:
    Spell(std::string name, std::string description, int weak, int base, int strong, std::string element): Item(name,description) , weak(weak), base(base), strong(strong), element(element) {}
    ~Spell() {}
    int get_weak();
    int get_strong();
    int get_base();
    std::string get_element();
    
private:
    int base; // base attack
    int weak; //weak attack 
    int strong;  // strong attack
    std::string element; // element that spell fall under
};

class Potion : public Item {
public:
    Potion(std::string name, std::string description, int value, int quantity) : Item(name, description), value(value), quantity(quantity) {}
    ~Potion() {}
    int get_value();
    int get_quantity();
    void set_quantity(int value);
    bool use_potion(Player* p);

private:
    int value;  // health value
    int quantity; // quantity 

};