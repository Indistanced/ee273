#include "combat.h"

#include <string>
#include <limits>

bool startCombat(Player* p, std::string enemy_name, int health, int attack, std::string element) {

	Enemy e(enemy_name, health, attack, element);
	std::cout << "\033[3J\033[H\033[2J"; 
	std::cout << "\n---- Combat ----\n";

	while (p->isAlive() && e.isAlive()) {
		std::cout << "\nPlayer Health: " << p->getHealth() << "\n";      // Display player health
		std::cout << e.getName() << " Health: " << e.getHealth() << "\n";   // Display enemy health

		int choice = 0;
		std::cout << "\n---- Player's Move ----\n";    // Player attack move
		std::cout << "1) Cast a spell\n";
		std::cout << "2) Use a potion\n";
		std::cout << "choice: ";
		std::cin >> choice;

		if (choice == 1) {

			std::vector<Spell*> spells = p->getInventory().getSpells(); // Get list of spells

			if (spells.empty()) {
				std::cout << "\nYou have no spells!\n";
				continue;
			}
			p->getInventory().displaySpells();  // Display all spells for player to choose from

			int spellChoice;

			do {
				std::cout << "Choose spell: ";  
				std::cin >> spellChoice;   // Get spell index

				if (spellChoice < 1 || spellChoice > spells.size()) {
					std::cout << "\nInvalid choice, try again.\n";   // Check for invalid choice 
				}

			} while (spellChoice < 1 || spellChoice > spells.size());

			Spell* sp = spells[spellChoice - 1];   // Get selected spell 

			int damage = p->getStrength() + rand() % 10;   // Base damage (will increase with players strength)

			if (sp->get_element() == e.get_element()) {
				damage += sp->get_weak();     // Add weak spell damage if enemy has same element as spell
				std::cout << "\nYour spell was not very effective.\n";  
			}

			else if (sp->get_element() == e.get_weakness_element()) {
				damage += sp->get_strong();  // Add strong damage if spell is strong against enemy
				std::cout << "\nYour spell was super effective!\n";
			}

			else {
				damage += sp->get_base();  // If spell is not strong or weak, add base damage
			}

			e.takeDamage(damage);  // Update enemy health

			std::cout << "\nYou cast " << sp->get_name()
				<< " for " << damage << " damage!\n";
		}
	
		else if (choice == 2) {
			 
			std::vector<Potion*> potions = p->getInventory().getPotions();  // Get list of potions

			if (potions.empty()) {
				std::cout << "\nYou have no potions!\n";
				continue;
			}

			p->getInventory().displayPotions();  // Display all potions for player to choose from

			int potionChoice;
			do {
				std::cout << "Choose potion: ";  // Get potion index
				std::cin >> potionChoice;

				if (potionChoice < 1 || potionChoice > potions.size()) {  // Check for invaild index
					std::cout << "\nInvalid choice, try again.\n"; 
				}

			} while (potionChoice < 1 || potionChoice > potions.size());

			Potion* po = potions[potionChoice - 1];   // Get selected potion 

			if (po->use_potion(p)) {

				std::cout << "\nHealth: " << p->getHealth() << "/" << p->getMaxHealth() << "\n"; 

				
				if (po->get_quantity() == 0) {
					p->getInventory().removeItem(po);  // Remove potion if quantity reaches 0
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
		return true; // Can progress in game
	}
	else {
		std::cout << "\n\nYou were defeated... \n";
		return false; // Will be asked to restart
	}
}