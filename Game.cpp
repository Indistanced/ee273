#include <iostream> // Read and write functionality with console
#include <fstream> // Read and write functionality with files
#include <string> // Enable strings
#include <map> // Enable maps

#include "Player.h"
#include "Game.h"
#include "clear.h"
#include "unicode.h"
#include "combat.h"
#include "Game_Level.h"
#include "win.h"
#include "menu.h"

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

	outFile << "Player name: " << p->getName() << '\n';
	outFile << "Current health: " << p->getHealth() << '\n';
	outFile << "Maximum health: " << p->getMaxHealth() << '\n';
	outFile << "Level: " << p->getLevel() << '\n';
	outFile << "Experience Points: " << p->getExp() << '\n';
	outFile << "Strength: " << p->getStrength() << '\n';
	outFile << "Location: " << p->location << "\n\n";

	auto& items = p->getInventory().getItems();

	outFile << "Items: " << items.size() << "\n";

	for (auto* item : items)
	{
		if (Potion* po = dynamic_cast<Potion*>(item)) {
			outFile << "Potion: "
				<< po->get_name() << "\nDescription: "
				<< po->get_description() << "\nValue: "
				<< po->get_value() << "\nQuantity: "
				<< po->get_quantity() << "\n\n";
		} else if (Spell* sp = dynamic_cast<Spell*>(item)) {
			outFile << "Spell: "
				<< sp->get_name() << "\nDescription: "
				<< sp->get_description() << "\nBase damage: "
				<< sp->get_base() << "\nWeak damage: "
				<< sp->get_weak() << "\nStrong damage: "
				<< sp->get_strong() << "\nElement: "
				<< sp->get_element() << "\n";
		}
	}
	
	auto& quests = p->getQuests();   

	outFile << "Quests: " << quests.size() << "\n";

	for (auto& q : quests) {
		outFile << q.first << " | "
				<< (q.second ? "Complete" : "Incomplete") << "\n";
	} return true;
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
	Game::gout() << "You step into a lush green hill range full of flowers.\n";
	Game::gout() << "You progress on in your journey...\n\n";

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

	// LEVEL COMPLETE
	std::cout << "\nYou completed Level 1!\n";
	p->completeQuest("Take down the fire spirit");
	Level::isComplete[0] = true;

	save_player(p);

	return true;
}

bool Game::level_two_choices(int choice, Combat* c) {
	if (choice == 1) { // ATTACK
		if (!c->startCombat(p, "Slime", 50, 8, "water")) return false;
	} else if (choice == 2) { // RUN
		Game::gout() << "\nThe Mushroom Warrior is catching up to you\n";
		Game::gout() << "Running away is a form of disrespect in their eyes\n";
		Game::gout() << "You have offended it and you cannot evade it. What will you do?\n\n";
		playerInstanceOptions(choice, "ATTACK", "STAY");
		if (choice == 1) level_two_choices(1, c); // ATTACK
		else if (choice == 2) level_two_choices(3, c); // STAY
	} else if (choice == 3) { // STAY
		Game::gout() << "You hand a stick to the warrior as as an attempt to ease the hostility";
		std::cout << "???: AweR44 60Jlas w asd";
		Game::gout() << "It seems that his compadres have been alerted. They troddle towards you, dragging their mushroom helmets"
					 << "(FUN FACT: mushroom helmets are a part of their bone structure, just as tortoises have shells as part of their skeletal structure)";
		Game::gout() << "You tell warriors your mission, and they thus deem you to be of no harm to them,"
			<< "and decide to give you a gift to aid you in your journey.";
	}
}

bool Game::level_two() {
	int choice;
	Combat* c = new Combat();

	terminateBuffer();

	std::cout << "═════════════════════════ MAGIC MOUNTAIN ═════════════════════════\n";
	Game::gout() << "As I venture through this forest engorged with shrooms, I can't help but wonder why this place was one of his fondest memories.\n";
	Game::gout() << "As per the memoir, this was perhaps the last place on Earth devoid of human endeavour (aside from perhaps unliveable areas in the Arctic,"
				 << "Antarctic, and the Sahara...).\n\n";
	Game::gout() << "I smell something...\n\n";

	// Enemy 1

	std::cout << "???: " << "ARHGH!!!\n\n";
	Game::gout() << "A wild Mushroom Warrior has emerged from the marshlands embedded in the forest\n";
	ask_to_continue();
	
	Game::gout() << "\nWhat shall your plan of action be?\n";
	
	playerInstanceOptions(choice, "Attack", "Run", "Stay");
	level_two_choices(choice, c);

	// LEVEL COMPLETE
	Level::isComplete[1] = true;
	save_player(p);

	return true;
}

bool Game::level_three() {
	Combat* c = new Combat();

	terminateBuffer();

	std::cout << "═════════════════════════ THE ARM OF DISMAY ═════════════════════════\n";
	Game::gout() << "You leave step into a lush green hill range full of flowers.\n";
	Game::gout() << "You progress on in your journey...\n\n";

	// LEVEL COMPLETE
	Level::isComplete[1] = true;
	save_player(p);

	return true;
}

void Game::level_selection() {
	auto first = Level::names.begin();
	auto second = std::next(first);
	auto third = std::next(second);

	if (p->location == "Town") {
		p->location = first->first;
		std::cout << "You are entering level " << Level::names[p->location] << std::endl;

		if (!level_one()) {
			std::cout << "Game over!";
		} ask_to_continue();
		p->location = second->first;
		return;
	}

	if (p->location == second->first) {
		std::cout << "You are entering level " << Level::names[p->location] << std::endl;
		if (!level_two()) {
			std::cout << "Game over!";
		} ask_to_continue();
		p->location = third->first;
		return;
	}

	if (p->location == third->first) {
		std::cout << "You are entering level " << Level::names[p->location] << std::endl;
		if (!level_three()) {
			std::cout << "Game over!";
		} ask_to_continue();
		p->location = "End";
		return;
	}
}

void Game::menu(Player* p) {

	int choice;
	bool quit = false;
	std::map<std::string, int> level = { {"Green Hill Zone", 1 }, { "Magic Mountain", 2 }, { "The Arm of Dismay", 3 } };

	do {
		Sleep(1);
		terminateBuffer();
		enbox("Player Menu"); std::cout << '\n';

		DisplayMinimap();

		std::cout << "1) Display player stats\n";
		std::cout << "2) View Inventory\n";
		std::cout << "3) View Quests\n";
		std::cout << "4) Go to Game\n";
		std::cout << "5) Save Game\n";
		std::cout << "6) Quit\n";

		do {
			std::cout << "Choice: ";
			std::cin >> choice;

			if (choice < 1 || choice > 6) { // If invalid choice, clear input before re-running
				std::cout << "Invalid choice, try again.";
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
			} std::cout << std::endl;

			auto first = Level::names.begin();
			auto second = std::next(first);
			auto third = std::next(second);

			level_selection();
			if (p->location == first->first || p->location == second->first || p->location == third->first) {
				break;
			} break;
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