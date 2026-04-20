//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 14/03/26

//Changes made:
//- updated game menu with player stats 
//- updated game menu with inventory display
//- updated game menu with quest display
//- updated save and quit options
//- updated save file with location, level, experience, inventory and quests
//- added in level story and combat interaction for levels 1 to 3

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
#include "main.h"

Game* Game::instance = nullptr; // Tells class that the game initially hasn't been created

Game* Game::getInstance(Player* p) {
	if (instance == nullptr) { // If game hasn't been created yet
		instance = new Game(p); // Create an instance of the game
	} return instance;
}

int gameOver(Player* p) {
	return 0;
}

void Game::level_selection(int& choice) {
	auto first = Level::names.begin();
	auto second = std::next(first);
	auto third = std::next(second);

	if (p->getLocation() == "Town") {
		p->setLocation(first->first);

		if (!level_one()) {
			if (!gameOverMenu(p)) {
				//p->setLocation("Town");
				//ask_to_continue();
				return;
			}
			else return;
			//ask_to_continue();
		}
		else {
			p->setLocation(second->first);
			playerInstanceOptions(choice, "Continue", "Close Game", "INVALID", "\nCONTINUE?");
		} return;
	}

	if (p->getLocation() == second->first) {
		if (!level_two()) {
			if (gameOverMenu(p)) {
				p->setLocation("Town");
				//ask_to_continue();
				return;
			}
			else return;
		}
		else {
			p->setLocation(third->first);
			playerInstanceOptions(choice, "Continue", "Close Game", "INVALID", "\nCONTINUE?");
		} return;

	}

	if (p->getLocation() == third->first) {
		if (!level_three()) {
			if (gameOverMenu(p)) {
				p->setLocation("Town");
				//ask_to_continue();
				return;
			}
			else return;
		}
		else {
			p->setLocation("End");

			playerInstanceOptions(choice, "Complete Game", "INVALID", "INVALID", "\nCONTINUE?");
			return;
		}
	}
}

// Save Game function
bool Game::save_player(Player*& p) {
	const std::string file_name = "game_save_file.txt"; // Constant load file path (eliminates user error)

	std::ofstream outFile(file_name);

	if (!outFile) {
		std::cerr << "Error opening file: " << file_name << '\n';
		return false;
	}

	outFile << p->getName() << "\n";
	outFile << p->getHealth() << "\n";
	outFile << p->getMaxHealth() << "\n";
	outFile << p->getLevel() << "\n";
	outFile << p->getExp() << "\n";
	outFile << p->getExpLimit() << "\n";
	outFile << p->getStrength() << "\n";
	outFile << p->getLocation() << "\n";

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
	terminateBuffer();

	gout() << "Welcome, Adventurer " << p->getName() << "!\n"; // Introductory message
	std::cout << "── Entering the " << p->getLocation() << " ──\n"; xbar(); std::cout << '\n'; // Location information
	std::cout << ">> Press enter to start <<"; // Confirmation

	clearBuffer();
	std::cin.get();  // wait for player to press enter
	return;
}

bool Game::run(Game* g, Player* p) {
	start(p);
	save_player(p);
	menu(p);

	return p->isAlive();
}

std::ostream& Game::gout() {
	return std::cout << ">> ";
}


bool Game::quit_game() {

	terminateBuffer();
	std::string answer;

	while (true) {
		std::cout << "\n>> Are you sure you want to exit?\n";
		std::cout << "\t>> Yes (Y) / No (N) <<\n";

		std::cout << "Choice: ";
		std::cin >> answer;

		for (char& c : answer) {
			c = tolower(c);
		}

		if (answer == "yes" || answer == "y") {
			return true;
		}
		else if (answer == "no" || answer == "n") {
			return false;
		}
		else {
			std::cout << "Invalid response, try again.\n\n";
		}
	}

}

bool Game::level_one() {
	Combat c;

	terminateBuffer();

	std::cout << "You are entering level " << Level::names["Green Hill Zone"] << "\n\n";

	std::cout << "═════════════════════════ GREEN HILL ZONE ═════════════════════════\n";
	Game::gout() << "You step into a lush green hill range full of flowers.\n";
	Game::gout() << "You progress on in your journey...\n\n";

	Game::gout() << "All of a sudden, something jumps up at you out of nowhere!\n";

	// Enemy 1 

	Game::gout() << "A water slime appears!\n";
	ask_to_continue();
	if (!c.startCombat(p, "Slime", 50, 8, "water")) {
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
	if (!c.startCombat(p, "Goblin", 70, 10, "grass")) {
		return false;
	}

	ask_to_continue();

	// Enemy 3 (boss battle)

	terminateBuffer();

	Game::gout() << "You reach the top of the hill...\n";
	Game::gout() << "A powerful fire spirit blocks your path!\n";
	ask_to_continue();
	if (!c.startCombat(p, "Fire Spirit", 100, 12, "fire")) {
		return false;
	}

	// LEVEL COMPLETE
	std::cout << "\nYou completed Level 1!\n";
	p->completeQuest("Take down the fire spirit");
	Level::isComplete[0] = true;

	Game::gout() << "You have a new quest! - Reach the portal at the peak of the Magic Mountain\n\n";
	p->addQuest("Reach the portal at the peak of the Magic Mountain", false);

	save_player(p);

	return true;
}


bool Game::level_two() {
	Combat c;

	terminateBuffer();

	std::cout << "You are entering level " << Level::names["Magic Mountain"] << "\n\n";

	std::cout << "═════════════════════════ MAGIC MOUNTAIN ═════════════════════════\n";







	Game::gout() << "You enter a mystical place.\n";
	Game::gout() << "You look around and admire the mystical atmosphere of the mountain.\n";
	Game::gout() << "You progress on in your journey up the mountain...\n\n";

	Game::gout() << "Suddenly, a rock starts to move!\n";

	// Enemy 1 

	Game::gout() << "A Grass Golem awakens!\n";
	ask_to_continue();
	if (!c.startCombat(p, "Golem", 120, 12, "Golem")) {
		return false;
	}

	Game::gout() << "\nThe Golem perishes, but not without a warning...\n";
	std::cout << "Beware of the Water Serpent";

	Game::gout() << "\nYou have a new quest! - Take down the Water Serpent\n";
	p->addQuest("Take down the fire spirit", false);

	ask_to_continue();

	// Enemy 2 
	terminateBuffer();

	Game::gout() << "You move ascend further up the mountain...\n";
	Game::gout() << "You stumble on a rock and fall into a bird nest.\n";
	Game::gout() << "A Firebird takes you as a threat and attacks!\n";
	ask_to_continue();
	if (!c.startCombat(p, "Firebird", 150, 15, "fire")) {
		return false;
	}

	// Enemy 3 (boss battle)
	terminateBuffer();

	Game::gout() << "You reach the peak of the mountain...\n";
	Game::gout() << "A terrifying water serpent radiating with magic stands between you and the portal!\n";
	ask_to_continue();
	if (!c.startCombat(p, "Water Serpent", 200, 20, "water")) {
		return false;
	}

	std::cout << "\nYou completed a quest! - Take down the Water Serpent\n";
	p->completeQuest("Take down the Water Serpent");

	// LEVEL COMPLETE
	Game::gout() << "\n\nYou compose yourself and go through the portal.\n";
	std::cout << "\n-- You completed Level 2! --\n";

	std::cout << "\nYou completed a quest! - Reach the portal at the peak of the Magic Mountain\n\n";
	p->completeQuest("Reach the portal at the peak of the Magic Mountain");
	Level::isComplete[1] = true;

	Game::gout() << "\n\nYou have a new quest! - concur The Arm of Dismay\n";
	p->addQuest("Conquer the Arm of Dismay", false);

	save_player(p);

	return true;
}

bool Game::level_three() {

	Combat c;

	terminateBuffer();

	std::cout << "You are entering level " << Level::names["The Arm of Dismay"] << "\n\n";

	std::cout << "═════════════════════════ THE ARM OF DISMAY ═════════════════════════\n";
	Game::gout() << "You come of a the portal and sense a dark presence...\n";
	Game::gout() << "You look around and feel a sense of dread.\n";
	Game::gout() << "You progress on in your journey through the dark dungeon...\n\n";

	// Enemy 1 
	Game::gout() << "You cross a bridge over a lava pit\n";
	Game::gout() << "Suddenly, something rises from the flames!\n";
	Game::gout() << "An Ember Titan!\n";
	ask_to_continue();
	if (!c.startCombat(p, "Ember Titan", 220, 25, "fire")) {
		return false;
	}


	// Enemy 2 
	terminateBuffer();

	Game::gout() << "You move further through the dungeon...\n";
	Game::gout() << "The air suddenly grows cold and damp.\n";
	Game::gout() << "Water begins to drip from the ceiling...\n";
	Game::gout() << "A pool forms beneath your feet.\n";
	Game::gout() << "Without warning, it surges upward!\n";
	Game::gout() << "An Aqua Phantom emerges!\n";

	ask_to_continue();
	if (!c.startCombat(p, "Aqua Phantom", 250, 30, "water")) {
		return false;
	}

	// Enemy 3 (boss battle)
	terminateBuffer();

	Game::gout() << "You step into a vast chamber...\n";
	Game::gout() << "Strangely... vines cover the walls.\n";
	Game::gout() << "Roots twist through the stone, pulsing with life.\n";
	Game::gout() << "The ground begins to shift beneath you.\n";
	Game::gout() << "A massive form rises.\n";
	Game::gout() << "Thornheart Dragon awakens!\n";
	ask_to_continue();
	if (!c.startCombat(p, "Thornheart Dragon", 300, 35, "grass")) {
		return false;
	}

	// LEVEL COMPLETE
	std::cout << "\nYou completed a quest! - concur The Arm of Dismay\n\n";
	p->completeQuest("concur The Arm of Dismay");

	Game::gout() << "The Dragon lets out a deep groan as the vines wither away...\n";
	Game::gout() << "The dungeon falls silent.\n";
	Game::gout() << "You stand victorious.\n\n";

	Level::isComplete[2] = true;
	save_player(p);

	return true;
}

//bool Game::level_two_choices(int choice, Combat* c) {
//	if (choice == 1) { // ATTACK
//		if (!c->startCombat(p, "Slime", 50, 8, "water")) return false;
//	}
//	else if (choice == 2) { // RUN
//		Game::gout() << "\nThe Mushroom Warrior is catching up to you\n";
//		Game::gout() << "Running away is a form of disrespect in their eyes\n";
//		Game::gout() << "You have offended it and you cannot evade it. What will you do?\n\n";
//		playerInstanceOptions(choice, "ATTACK", "STAY");
//		if (choice == 1) level_two_choices(1, c); // ATTACK
//		else if (choice == 2) level_two_choices(3, c); // STAY
//	}
//	else if (choice == 3) { // STAY
//		Game::gout() << "You hand a stick to the warrior as as an attempt to ease the hostility";
//		std::cout << "???: AweR44 60Jlas w asd";
//		Game::gout() << "It seems that his compadres have been alerted. They troddle towards you, dragging their mushroom helmets"
//			<< "(FUN FACT: mushroom helmets are a part of their bone structure, just as tortoises have shells as part of their skeletal structure)";
//		Game::gout() << "You tell warriors your mission, and they thus deem you to be of no harm to them,"
//			<< "and decide to give you a gift to aid you in your journey.";
//	}
//}
//
//bool Game::level_two() {
//	int choice;
//	Combat* c = new Combat();
//	 
//	terminateBuffer();
//
//	std::cout << "═════════════════════════ MAGIC MOUNTAIN ═════════════════════════\n";
//	Game::gout() << "As I venture through this forest engorged with shrooms, I can't help but wonder why this place was one of his fondest memories.\n";
//	Game::gout() << "As per the memoir, this was perhaps the last place on Earth devoid of human endeavour (aside from perhaps unliveable areas in the Arctic,"
//		<< "Antarctic, and the Sahara...).\n\n";
//	Game::gout() << "I smell something...\n\n";
//
//	// Enemy 1
//
//	std::cout << "???: " << "ARHGH!!!\n\n";
//	Game::gout() << "A wild Mushroom Warrior has emerged from the marshlands embedded in the forest\n";
//	ask_to_continue();
//
//	Game::gout() << "\nWhat shall your plan of action be?\n";
//
//	playerInstanceOptions(choice, "Attack", "Run", "Stay");
//	level_two_choices(choice, c);
//
//	// LEVEL COMPLETE
//	Level::isComplete[1] = true;
//	save_player(p);
//
//	return true;
//}

void Game::resetInstance() {
	instance = nullptr;
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

			std::cout << "─── PLAYER STATS ───\n";
			p->to_string();
			ask_to_continue();
			break;
		}
		case 2: {
			terminateBuffer();

			p->getInventory().displayItems(p);
			break;
		} case 3: {
			terminateBuffer();

			std::cout << "─── Quest List ───\n";
			p->quests_to_string();
			ask_to_continue();
			break;
		} case 4: {
			auto first = Level::names.begin();
			auto second = std::next(first);
			auto third = std::next(second);

			int choice{};

			terminateBuffer();

			for (auto& l : level) {
				std::cout << l.first << ": " << l.second << std::endl;
			} std::cout << std::endl;

			level_selection(choice);

			//if (choice) save_player(p);
			return;
			// need a way to return if level is not complete
		} 
		case 5: {
			terminateBuffer();
			save_player(p);
			std::cout << "\t>> Game saved <<\n";
			ask_to_continue();
			break;
		} case 6: {
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