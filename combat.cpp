#include "combat.h"

#include <string>
#include <limits>

void Combat::playerMove(Player* p, Enemy& e) {

	int choice = 0;
	do {
		std::cout << "\n═══════ Player's Move ═══════\n\n";
		std::cout << "1) Cast a spell\n";
		std::cout << "2) Use a potion\n";
		std::cout << "choice: ";
		std::cin >> choice;

		if (choice == 1) {

			auto spells = p->getInventory().getSpells();

			if (spells.empty()) {
				std::cout << "\nYou have no spells!\n";
				return;
			}

			p->getInventory().displaySpells();

			int spellChoice;
			do {
				std::cout << "Choose spell: ";
				std::cin >> spellChoice;
			} while (spellChoice < 1 || spellChoice > spells.size());

			Spell* sp = spells[spellChoice - 1];

			int damage = p->getStrength() + rand() % 10;

			if (sp->get_element() == e.get_element()) {
				damage += sp->get_weak();
				std::cout << "\nYour spell was not very effective.";
			}
			else if (sp->get_element() == e.get_weakness_element()) {
				damage += sp->get_strong();
				std::cout << "\nYour spell was super effective!";
			}
			else {
				damage += sp->get_base();
			}

			e.takeDamage(damage);

			std::cout << "\nYou cast " << sp->get_name()
				<< " for " << damage << " damage!\n";
		}

		else if (choice == 2) {

			auto potions = p->getInventory().getPotions();

			if (potions.empty()) {
				std::cout << "\nYou have no potions!\n";
				return;
			}

			p->getInventory().displayPotions();

			int potionChoice;
			do {
				std::cout << "Choose potion: ";
				std::cin >> potionChoice;
			} while (potionChoice < 1 || potionChoice > potions.size());

			Potion* po = potions[potionChoice - 1];

			if (po->use_potion(p)) {
				std::cout << "\nHealth: " << p->getHealth()
					<< "/" << p->getMaxHealth() << "\n";

				if (po->get_quantity() == 0) {
					p->getInventory().removeItem(po);
				}
			}
			else {
				std::cout << "\nYou have no potions left.\n";
			}
		}

		else {
			std::cout << "\nInvalid choice.\n";
		}
	} while (choice != 1);
}

void Combat::enemyMove(Player* p, Enemy& e) {
	std::cout << "\n═══════ Enemy Attack ═══════\n\n";

	int damage = 0;
	int randNum = rand() % 3; //0 to 2

	if (randNum == 0) {
		damage = e.getStrength() + (rand() % 10 + 5); // strong attak damage
		std::cout << "The enemy attacks aggressively!\n";
	}
	else if (randNum == 1) {
		damage = e.getStrength() + rand() % 5; // low attack damage
		int heal = e.getMaxHealth() / 10;
		if (heal < 1) {
			heal = 1;
		}
		e.addHealth(heal); // gains 10% of health back
		std::cout << "The enemy plays defensively and recovers some health!\n";
	}
	else { 
		damage = e.getStrength() + rand() % 10; //basic attack  
		std::cout << "The enemy attacks!\n";   
	}

	std::cout << "The " << e.getName()
		<< " hit you for " << damage << " damage!\n";

	p->takeDamage(damage);
}


bool Combat::startCombat(Player* p, std::string enemy_name, int health, int attack, std::string element) {

	Enemy e(enemy_name, health, attack, element);

	while (p->isAlive() && e.isAlive()) {
		// PLAYER TURN
		std::cout << "\033[3J\033[H\033[2J";
		std::cout << "\n══════════════ Combat ══════════════\n";

		std::cout << "\nPlayer Health: " << p->getHealth() << "\n";
		std::cout << e.getName() << " Health: " << e.getHealth() << "\n";

		playerMove(p, e);
		if (!e.isAlive()) break;
		system("pause");

		// ENEMY TURN
		std::cout << "\033[3J\033[H\033[2J";
		std::cout << "\n══════════════ Combat ══════════════\n";

		std::cout << "\nPlayer Health: " << p->getHealth() << "\n";
		std::cout << e.getName() << " Health: " << e.getHealth() << "\n";

		enemyMove(p, e);
		if (!e.isAlive()) break;
		system("pause");

	}

	// END

	if (p->isAlive()) {
		std::cout << "\n\nCongratulations you defeated the " << e.getName() << "!\n";
		std::cout << "-- You Gained +" << e.getMaxHealth() << " Experience! --\n";

		p->addExp(e.getMaxHealth());

		std::cout << "\nThe " << e.getName() << " dropped:\n";
		item_drop_generator(p, e.getMaxHealth());

		return true;
	}

	std::cout << "\n\nYou were defeated...\n";
	return false;
}

void Combat::item_drop_generator(Player* p, int enemy_health) {

	int rand_num = rand() % 101; // 0 to 100
	int rand_element = rand() % 3; // 0 to 2

	//lower teir of drops
	if (enemy_health <= 50) {
		std::cout << "- Small Health Potion\n";
		p->getInventory().addPotion("Small Health Potion", "Restores 25 HP", 25, 1);

		if (rand_num < 70) {
			if (rand_element == 0) {
				if (p->getInventory().addSpell("Water Ball", "Weak water ability", 18, 15, 25, "water")) {
					std::cout << "- Water ball spell\n";
				}
			}
			else if (rand_element == 1) {
				if (p->getInventory().addSpell("Fire Ball", "Weak fire ability", 18, 15, 25, "fire")) {
					std::cout << "- Fire Ball spell\n";
				}
			}
			else {
				if (p->getInventory().addSpell("Vine Whip", "Weak grass ability", 18, 15, 25, "grass")) {
					std::cout << "- Vine Whip spell\n";
				}
			}
		}
	}
	else if (enemy_health <= 100) {
		std::cout << "- Medium Health Potion\n";
		p->getInventory().addPotion("Medium Health Potion", "Restores 50 HP", 50, 1);

		if (rand_num < 60) {
			if (rand_element == 0) {
				if (p->getInventory().addSpell("Water Wave", "Medium water ability", 30, 20, 35, "water")) {
					std::cout << "- Water Wave spell\n";
				}
			}
			else if (rand_element == 1) {
				if (p->getInventory().addSpell("Flame Rush", "Medium fire ability", 30, 20, 35, "fire")) {
					std::cout << "- Flame Rush spell\n";
				}
			}
			else {
				if (p->getInventory().addSpell("Grass Spikes", "Medium grass ability", 30, 20, 35, "grass")) {
					std::cout << "- Grass Spikes spell\n";
				}
			}
		}
	}

	else {
		std::cout << "- Large Health Potion\n";
		p->getInventory().addPotion("Large Health Potion", "Restores 50 HP", 75, 1);

		if (rand_num < 50) {
			if (rand_element == 0) {
				if (p->getInventory().addSpell("Hydro Connon", "Strong water ability", 40, 30, 55, "water")) {
					std::cout << "- Hydro Cannon spell\n";
				}
			}
			else if (rand_element == 1) {
				if (p->getInventory().addSpell("Inferno", "Strong fire ability", 40, 30, 55, "fire")) {
					std::cout << "- Inferno spell\n";
				}
			}
			else {
				if (p->getInventory().addSpell("Leaf Tornado", "Strong grass ability", 40, 30, 55, "grass")) {
					std::cout << "- Leaf Tornado spell\n";
				}
			}
		}
	}

}