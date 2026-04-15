#include <iostream> // Read and write functionality with console
#include <fstream> // Read and write functionality with files
#include <string> // Enable strings
#include <map> // Enable maps

#include "Player.h"
#include "Game.h"
#include "clear.h"
#include "unicode.h"
#include "combat.h"

Game* Game::instance = nullptr; // Tells class that the game initially hasn't been created

Game* Game::getInstance(Player* p) {
	if (instance == nullptr) { // If game hasn't been created yet
		instance = new Game(p); // Create an instance of the game
	} return instance;
}

bool Game::save_player(Player*& p) {
	const std::string file_name = "game_save_file.txt"; // Constant load file path (eliminates user error)

	std::string name{}, location{};
	int hp{}, maxHp{}, strength{};

	std::ofstream outFile(file_name);

	if (!outFile) {
		std::cerr << "Error opening file: " << file_name << '\n';
		return false;
	}

	// WRITE PLAYER DATA TO TEXT FILE

	outFile << p->getName() << '\n';
	outFile << p->getHealth() << '\n';
	outFile << p->getMaxHealth() << '\n';
	outFile << p->getLevel() << '\n';
	outFile << p->getExp() << '\n';
	outFile << p->getStrength() << '\n';
	outFile << p->location << '\n';

	auto& items = p->getInventory().getItems();

	outFile << items.size() << "\n";

	for (auto* item : items)
	{
		if (Potion* po = dynamic_cast<Potion*>(item)) {
			outFile << "potion,"
				<< po->get_name() << ","
				<< po->get_description() << ","
				<< po->get_value() << ","
				<< po->get_quantity() << "\n";
		} else if (Spell* sp = dynamic_cast<Spell*>(item)) {
			outFile << "spell,"
				<< sp->get_name() << ","
				<< sp->get_description() << ","
				<< sp->get_base() << ","
				<< sp->get_weak() << ","
				<< sp->get_strong() << ","
				<< sp->get_element() << "\n";
		}
	}
	
	auto& quests = p->getQuests();   

	outFile << quests.size() << "\n";

	for (auto& q : quests) {
		outFile << q.first << "|"
			<< (q.second ? "Complete" : "Incomplete") << "\n";
	}
	return true;
}

void Game::start(Player* p) {
	std::string start;
	terminateBuffer();

	gout() << "Welcome, Adventurer " << p->getName() << "!\n"; // Introductory message
	std::cout << u8"── Entering the " << p->location << u8" ──\n"; xbar(); std::cout << '\n'; // Location information
	std::cout << ">> Press enter to start <<"; // Confirmation

	clearBuffer();

	std::getline(std::cin, start); // Return when new line (enter is received)
	return;
}

void Game::run(Game* g, Player* p) {
	start(p);
	save_player(p);
	menu(p);
}

std::ostream& Game::gout() {
	return std::cout << ">> ";
}


bool Game::quit_game() {

	std::string answer;

	std::cout << "\n>> Are you sure you want to exit?\n";
	std::cout << "\t>> Yes (Y) / No (N) <<\n";
	std::cout << "Choice: ";
	std::cin >> answer;

	for (char& c : answer) {
		c = tolower(c);
	}

	if (answer == "yes" || answer == "y") {
		return true;
	} return false;
}

void Game::ask_to_continue() {
	std::string input;

	std::cout << "\n>> Press enter to continue <<";

	clearBuffer();

	std::getline(std::cin, input); // Return when new line (enter is received)
	return;
}

bool Game::level_one() {
	Combat* c = new Combat();

	terminateBuffer();

	std::cout << "═════════════════════════ GREEN HILL ZONE ═════════════════════════\n";
	Game::gout() << "You leave step into a lush green hill range full of flowers.\n";
	Game::gout() << "You progress on in your jorney...\n\n";

	Game::gout() << "All of a sudden, something jumps up at you out of nowhere!\n";

	// Enemy 1 

	Game::gout() << "A water slime appears!\n";
	ask_to_continue();
	if (!c->startCombat(p, "Slime", 50, 8, "water")) {
		return false;
	}

	Game::gout() << "You completed a quest! - Defeat a slime\n\n";
	p->completeQuest("Defeat a slime");

	Game::gout() << "You have a new quest! - Take down the fire spirit";
	p->addQuest("Take down the fire spirit", false);

	ask_to_continue();

	// Enemy 2 

	terminateBuffer();

	Game::gout() << "You move deeper into the hills...\n";
	Game::gout() << "A wild grass goblin ambushes you!\n";
	ask_to_continue();
	if (!c->startCombat(p, "Goblin", 70, 10, "grass")) {
		return false;
	}

	ask_to_continue();

	// Enemy 3 (boss battle)

	terminateBuffer();

	Game::gout() << "You reach the top of the hill...\n";
	Game::gout() << "A powerful fire spirit blocks your path!\n";
	ask_to_continue();
	if (!c->startCombat(p, "Fire Spirit", 100, 12, "fire")) {
		return false;
	}

	// Level complete
	std::cout << "\nYou completed Level 1!\n";
	p->completeQuest("Take down the fire spirit");

	save_player(p);

	return true;
}

bool Game::level_two() {
	return 0;
}

bool Game::level_three() {
	return 0;
}

void Game::menu(Player* p) {

	int choice;
	bool quit = false;
	std::map<std::string, int> level = { {"Green Hill Zone", 1 }, { "Magic Mountain", 2 }, { "The Arm of Dismay", 3 } };

	do {
		terminateBuffer();
		enbox("Player Menu"); std::cout << '\n';

		std::cout << "1) Display player stats\n";
		std::cout << "2) View Inventory\n";
		std::cout << "3) View Quests\n";
		std::cout << "4) Go to Game\n";
		std::cout << "5) Save Game\n";
		std::cout << "6) Quit\n";

		do {
			std::cout << "Choice: ";
			std::cin >> choice;

			if (choice < 1 || choice > 6) { // If invaild choice, clear input before re-running
				std::cout << "Invaild choice, try again.";
				clearBuffer();
			}

		} while (choice < 1 || choice > 6);

		switch (choice) {
		case 1: {
			terminateBuffer();

			std::cout << u8"─── PLAYER STATS ───\n";
			p->to_string();
			ask_to_continue();
			break;
		}
		case 2: {
			terminateBuffer();

			p->getInventory().displayItems(p);
			break;
		}
		case 3: {
			terminateBuffer();

			std::cout << u8"─── Quest List ───\n";
			p->quests_to_string();
			ask_to_continue();
			break;
		}
		case 4: {
			terminateBuffer();

			for (auto& l : level) {
				std::cout << l.first << ": " << l.second << std::endl;
			} 
			std::cout << std::endl;

			if (p->location == "Town") {
				p->location = "Green Hill Zone";
				std::cout << "You are entering level " << level[p->location] << std::endl;
				ask_to_continue();

				if (!level_one()) {
					std::cout << "Game over!";
				} ask_to_continue();
			}
			break;
		}
		case 5: {
			terminateBuffer();
			save_player(p);
			std::cout << "\t>> Game saved <<\n";
			ask_to_continue();
			break;
		}
		case 6: {
			quit = quit_game();
			break;
		}
		default: {
			std::cout << "Invalid Choice.\n";
			break;
		};
		}

	} while (quit == false);
}