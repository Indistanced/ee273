#include "combat.h"

#include <string>
#include <limits>

bool startCombat(Player* p, std::string enemy_name, int health, int attack, std::string element) {

	Enemy e(enemy_name, health, attack, element);
	std::cout << "\033[3J\033[H\033[2J"; 
	std::cout << "\n---- Combat ----\n";

	while (p->isAlive() && e.isAlive()) {
		std::cout << "\nPlayer Health: " << p->getHealth() << "\n";      //display player health
		std::cout << e.getName() << " Health: " << e.getHealth() << "\n";   //display enemy health

		int choice = 0;
		std::cout << "\n---- Player's Move ----\n";    //player attack move
		std::cout << "1) Cast a spell\n";
		std::cout << "2) Use a potion\n";
		std::cout << "choice: ";
		std::cin >> choice;

		if (choice == 1) {

			std::vector<Spell*> spells = p->getInventory().getSpells(); // get list of spells

			if (spells.empty()) {
				std::cout << "\nYou have no spells!\n";
				continue;
			}
			p->getInventory().displaySpells();  //display all spells for player to choose from

			int spellChoice;

			do {
				std::cout << "Choose spell: ";  
				std::cin >> spellChoice;   // get spell index

				if (spellChoice < 1 || spellChoice > spells.size()) {
					std::cout << "\nInvalid choice, try again.\n";   // check for invalid choice 
				}

			} while (spellChoice < 1 || spellChoice > spells.size());

			Spell* sp = spells[spellChoice - 1];   // get selected spell 

			int damage = p->getStrength() + rand() % 10;   // base damage (will increase with players strength)

			if (sp->get_element() == e.get_element()) {
				damage += sp->get_weak();     // add weak spell damage if enemy has same element as spell
				std::cout << "\nYour spell was not very effective.\n";  
			}

			else if (sp->get_element() == e.get_weakness_element()) {
				damage += sp->get_strong();  // add strong damage if spell is strong against enemy
				std::cout << "\nYour spell was super effective!\n";
			}

			else {
				damage += sp->get_base();  // if spell is not strong or weak add base damage
			}

			e.takeDamage(damage);  // update enemey health

			std::cout << "\nYou cast " << sp->get_name()
				<< " for " << damage << " damage!\n";
		}
	
		else if (choice == 2) {
			 
			std::vector<Potion*> potions = p->getInventory().getPotions();  //get list of potions

			if (potions.empty()) {
				std::cout << "\nYou have no potions!\n";
				continue;
			}

			p->getInventory().displayPotions();  //display all potions for player to choose from

			int potionChoice;
			do {
				std::cout << "Choose potion: ";  //get potion index
				std::cin >> potionChoice;

				if (potionChoice < 1 || potionChoice > potions.size()) {  //check for invaild index
					std::cout << "\nInvalid choice, try again.\n"; 
				}

			} while (potionChoice < 1 || potionChoice > potions.size());

			Potion* po = potions[potionChoice - 1];   //get selected potion 

			if (po->use_potion(p)) {

				std::cout << "\nHealth: " << p->getHealth() << "/" << p->getMaxHealth() << "\n"; 

				
				if (po->get_quantity() == 0) {
					p->getInventory().removeItem(po);  //remove potion if quantity reaches 0
				}
			}
			else {
				std::cout << "\nYou have no potions left.\n";
			}
		}

		else {
			std::cout << "\nInvalid choice.\n";
			continue;
		}


		if (e.isAlive()) {
			std::cout << "\n---- Enemy Attck ----\n";

			int attack = e.getStrength() + rand() % 10;
			std::cout << "\nThe " << e.getName() << " hit you for " << attack << " damage!\n";

			p->takeDamage(attack);
		}

	}

	if (p->isAlive()) {
		std::cout << "\n\nYou defeated the " << e.getName() << "!\n";
		return true; // can progress in game
	}
	else {
		std::cout << "\n\nYou were defeated... \n";
		return false; // will be aksed to restart
	}
}