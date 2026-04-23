//Author:  Kyle Simpson and Aidan Kelly 
//Creation Date: 07/04/26

//Changes made:
//- Separate enemy and player attack cycles to enhance readability 
//- Add in extra enemy attack strategies
//- Add in random item drop change using rand() function
//- Add in exit game option to combat sequence 


#include "combat.h"
#include "unicode.h"
#include "Game.h"
#include "clear.h"
#include "Game_Level.h"

#include <string>
#include <limits>
#include <cstdlib>

void Combat::playerMove(Player* p, Enemy*& e) {

	int choice = 0;
	do {

		std::cout << "\n═══════ Player's Move ═══════\n\n";
		std::cout << "1) Cast a spell\n";
		std::cout << "2) Use a potion\n";
		std::cout << "3) Exit game\n\n";
		do {
			std::cout << "Choice: ";
			std::cin >> choice;

			if (choice < 1 || choice > 3 || std::cin.fail()) {
				clearBuffer();
				std::cout << "Invalid choice, try again.\n";
			}
		} while (choice < 1 && choice > 3);
		

		switch (choice) {
		case 1: {
			auto spells = p->getInventory().getSpells(); // Retrieve spells from inventory
			int spellChoice;

			// No spells in inventory
			if (spells.empty()) {
				std::cout << "\nYou have no spells!\n";
				return;
			}

			p->getInventory().displaySpells(); // Display spells from inventory (if available)

			// Input validation to ensure user selects a valid spell index
			do {
				clearBuffer();
				std::cout << "Choose spell: ";
				std::cin >> spellChoice;
			} while (spellChoice < 1 || spellChoice > spells.size() || std::cin.fail());

			Spell* sp = spells[spellChoice - 1]; // The chosen spell is selected

			int damage = p->getStrength() + rand() % 5; // An element of randomness is appended in the definition of the player strength attribute

			// Element X -> X = standard damage, Fire -> Water = weak damage, Water -> Fire = string damage, etc.
			if (sp->get_element() == e->get_element()) {
				damage += sp->get_weak(); // If the attacker has the element of the enemy's strength, the attack is ineffective
				dashText("Your spell was not very effective!");
			}
			else if (sp->get_element() == e->get_weakness_element()) {
				damage += sp->get_strong(); // If the attacker has the element of the enemy's weakness, the attack is effective
				dashText("Your spell was super effective!");
			}
			else {
				damage += sp->get_base(); // If the attacker has another element the base damage will be delt
			}

			e->takeDamage(damage); // Subtract the corresponding damage value from the enemy's health

			std::cout << "\nYou cast " << sp->get_name() << " for " << damage << " damage!\n";

			break;
		}
		case 2: {
			auto potions = p->getInventory().getPotions(); // Get all potions from inventory

			if (potions.empty()) { // Check to make sure player has potions
				std::cout << "\nYou have no potions!\n";
				break;
			}

			p->getInventory().displayPotions(); // Display all available potions 

			int potionChoice;
			// Get the user to select a potion
			do {
				clearBuffer();
				std::cout << "Choose potion: ";
				std::cin >> potionChoice;
			} while (potionChoice < 1 || potionChoice > potions.size() || std::cin.fail());

			Potion* po = potions[potionChoice - 1];  // Get the potion with the correct index

			// Try to use potion 
			if (po->use_potion(p)) {
				std::cout << "\nHealth: " << p->getHealth()
					<< "/" << p->getMaxHealth() << "\n";

				// If quantity drops to zero, remove potion from inventory 
				if (po->get_quantity() == 0) {
					p->getInventory().removeItem(po);
				} 

			}

			break;
		}
		case 3: {
			exit(0); // Quit program
		}
		default: std::cout << "\nInvalid choice.\n";
		}

	} while (choice != 1); // Loop until player attacks 
}



void Combat::enemyMove(Player* p, Enemy*& e) {
	std::cout << "\n═══════ Enemy Attack ═══════\n\n";

	int damage = 0;
	int randNum = rand() % 3; // 0 to 2

	if (randNum == 0) {
		damage = e->getStrength() + (rand() % 10 + 5); // Strong attack damage
		std::cout << "The enemy attacks aggressively!\n";
	}
	else if (randNum == 1) {
		damage = e->getStrength() + rand() % 5; // Low attack damage
		int heal = 1 + rand() % (e->getMaxHealth() / 10 + 1);
		e->addHealth(heal); // Gain health back
		std::cout << "The enemy plays defensively and recovers some health!\n";
	}
	else {
		damage = e->getStrength() + rand() % 10; // Basic attack  
		std::cout << "The enemy attacks!\n";
	}

	std::cout << "The " << e->getName()
		<< " hit you for " << damage << " damage!\n";

	p->takeDamage(damage);
}


bool Combat::startCombat(Player* p, std::string enemy_name, int health, int attack, std::string element) {

	Enemy* e = new Enemy(enemy_name, health, attack, element);  // Create enemy entity using stats

	while (p->isAlive() && e->isAlive()) {  // Game loop while both entities are alive 

		// PLAYER TURN

		clearBuffer();
		terminateBuffer();

		std::cout << "\n══════════════ Combat ══════════════\n";

		std::cout << "\nPlayer Health: " << p->getHealth() << "\n";
		std::cout << e->getName() << " Health: " << e->getHealth() << "\n";

		playerMove(p, e);  // Let player attack
		if (!e->isAlive()) break;  // Check if enemy is still alive
		system("pause");

		// ENEMY TURN

		clearBuffer();
		terminateBuffer();

		std::cout << "\n══════════════ Combat ══════════════\n";

		std::cout << "\nPlayer Health: " << p->getHealth() << "\n";
		std::cout << e->getName() << " Health: " << e->getHealth() << "\n";

		enemyMove(p, e); // Enemy move 
		if (!p->isAlive()) break; // Check if player is alive 
		system("pause");

	}

	// END

	if (p->isAlive()) {
		int exp = e->getMaxHealth() / 2; // Calculate experience 

		std::cout << '\n'; xbar(50); std::cout << '\n';

		std::cout << "\nCongratulations! You defeated the " << e->getName() << "!\n";
		std::cout << "  ── You Gained +" << exp << " Experience! ──\n";

		p->addExp(exp); // Add experience points to player 

		std::cout << "\nThe " << e->getName() << " dropped:\n";
		item_drop_generator(p, e->getMaxHealth());  //generate random items using enemy health
		delete e; // Delete enemy 
		return true;
	}

	std::cout << "\n\nYou were defeated...\n";
	delete e;
	return false;
}

void Combat::item_drop_generator(Player* p, int enemy_health) {

	// Pseudorandom number generators to randomise item drop generation 
	int rand_num = rand() % 101; // 0 to 100
	int rand_element = rand() % 3; // 0 to 2

	// Lower tier of drops
	if (enemy_health <= 50) {
		std::cout << "- Small Health Potion\n";
		p->getInventory().addPotion("Small Health Potion", "Restores +25 HP", 25, 1);

		if (rand_num < 70) {
			if (rand_element == 0) {
				if (p->getInventory().addSpell("Water Ball", "Weak water ability", 18, 8, 25, "water")) {
					std::cout << "- Water ball spell\n";
				}
			}
			else if (rand_element == 1) {
				if (p->getInventory().addSpell("Fire Ball", "Weak fire ability", 18, 8, 25, "fire")) {
					std::cout << "- Fire Ball spell\n";
				}
			}
			else {
				if (p->getInventory().addSpell("Vine Whip", "Weak grass ability", 18, 8, 25, "grass")) {
					std::cout << "- Vine Whip spell\n";
				}
			}
		}
	}

	// Medium tier drops
	else if (enemy_health <= 100) {
		std::cout << "- Medium Health Potion\n";
		p->getInventory().addPotion("Medium Health Potion", "Restores +50 HP", 50, 1);

		if (rand_num < 60) {
			if (rand_element == 0) {
				if (p->getInventory().addSpell("Water Wave", "Medium water ability", 25, 10, 35, "water")) {
					std::cout << "- Water Wave spell\n";
				}
			}
			else if (rand_element == 1) {
				if (p->getInventory().addSpell("Flame Rush", "Medium fire ability", 26, 10, 35, "fire")) {
					std::cout << "- Flame Rush spell\n";
				}
			}
			else {
				if (p->getInventory().addSpell("Grass Spikes", "Medium grass ability", 24, 10, 35, "grass")) {
					std::cout << "- Grass Spikes spell\n";
				}
			}
		}
	}

	// Upper-tier drops 
	else if (enemy_health <= 200) {
		std::cout << "- Large Health Potion\n";
		p->getInventory().addPotion("Large Health Potion", "Restores +75 HP", 75, 1);

		if (rand_num < 50) {
			if (rand_element == 0) {
				if (p->getInventory().addSpell("Hydro Cannon", "Strong water ability", 31, 10, 40, "water")) {
					std::cout << "- Hydro Cannon spell\n";
				}
			}
			else if (rand_element == 1) {
				if (p->getInventory().addSpell("Inferno", "Strong fire ability", 29, 10, 41, "fire")) {
					std::cout << "- Inferno spell\n";
				}
			}
			else {
				if (p->getInventory().addSpell("Leaf Tornado", "Strong grass ability", 30, 10, 39, "grass")) {
					std::cout << "- Leaf Tornado spell\n";
				}
			}
		}
	}

	// Legendary drops 
	else {
		std::cout << "- Mega Health Potion\n";
		p->getInventory().addPotion("Mega Health Potion", "Restores +100 HP", 100, 1);

		if (rand_num < 50) {
			if (rand_element == 0) {
				if (p->getInventory().addSpell("Tidal Cataclysm", "Legendary water ability", 35, 10, 46, "water")) {
					std::cout << "- Tidal Cataclysm spell\n";
				}
			}
			else if (rand_element == 1) {
				if (p->getInventory().addSpell("Emberstorm Dominion", "Legendary fire ability", 36, 10, 45, "fire")) {
					std::cout << "- Emberstorm Dominion spell\n";
				}
			}
			else {
				if (p->getInventory().addSpell("Nature’s Judgment", "Legendary grass ability", 34, 10, 44, "grass")) {
					std::cout << "- Nature’s Judgment spell\n";
				}
			}
		}
	}

	std::cout << "\n";
}