#include <iostream> // Read and write functionality with console
#include <fstream> // Read and write functionality with files
#include <string>
#include <map>

#include "Player.h"
#include "Game.h"
#include "clear.h"
#include "unicode.h"

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
		}
		else if (Spell* sp = dynamic_cast<Spell*>(item)) {
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
	gout() << "Welcome, Adventurer " << p->getName() << "!\n";
	std::cout << u8"── Entering the " << p->location << u8" ──\n";
	xbar(); std::cout << '\n';
	std::cout << ">> Press enter to start <<";
	clearBuffer();
	std::getline(std::cin, start); // Return when new line (enter is recived)
	return;
}

void Game::run(Game* g, Player* p) {
	start(p);
	save_player(p);
	menu(p);

	/*
	gout() << "What is your favourite number?\n"; // gout = cout (Game class)
	int num;
	Player::pin(p) >> num; // pin = cin (Player class)
	*/
}

std::ostream& Game::gout() {
	return std::cout << ">> ";
}


bool Game::quit_game() {

	std::string answer;

	std::cout << "\n>> Are you sure you want to exit?\n";
	std::cout << "\t>> yes / no <<\n";
	std::cout << "Choice: ";
	std::cin >> answer;

	for (char& c : answer) {
		c = tolower(c);
	}

	if (answer == "yes") {
		return true;
	}

	return false;
}

void Game::ask_to_continue() {
	std::string input;

	std::cout << "\n>> Press enter to continue <<";
	clearBuffer();
	std::getline(std::cin, input); // Return when new line (enter is recived)
	return;
}

void Game::level_one() {
	ask_to_continue();
	std::cout << u8"═════════════════════════ GREEN HILL ZONE ═════════════════════════";
}

void Game::menu(Player* p) {

	int choice;
	bool quit = false;
	std::map<std::string, int> level = { {"Green Hill Zone", 1 }, { "Magic Mountain", 2 }, { "The Arm of Dismay", 3 } };

	do {
		terminateBuffer();
		enbox("Player Menu");

		std::cout << "1) Display player stats\n";
		std::cout << "2) View Inventory\n";
		std::cout << "3) View Quests\n";
		std::cout << "4) Move Player\n";
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
		case 1:
			terminateBuffer();
			std::cout << u8"─── PLAYER STATS ───\n";
			p->to_string();
			ask_to_continue();
			break;
		case 2:
			terminateBuffer();
			p->getInventory().displayItems(p);
			break;
		case 4:
			terminateBuffer();
			for (auto& l : level) {
				std::cout << l.first << ": " << l.second << std::endl;
			} std::cout << std::endl;
			std::cout << "You are entering level " << level["Green Hill Zone"] << std::endl;
			ask_to_continue();
			break;
		case 5:
			terminateBuffer();
			save_player(p);
			std::cout << "\t>> Game saved <<\n";
			ask_to_continue();
			break;
		case 6:
			quit = quit_game();
			break;
		default:
			std::cout << "Not implemneted yet :/";
			break;
		};

	} while (quit == false);
}