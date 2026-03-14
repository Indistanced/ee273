#include <iostream> // Read and write functionality with console
#include <fstream> // Read and write functionality with files
#include <string>

#include "Player.h"
#include "game.h"


Game* Game::instance = nullptr; // Tells class that the game initially hasn't been created

Game* Game::getInstance(Player* p) {
	if (instance == nullptr) { // If game hasn't been created yet
		instance = new Game(p); // Create an instance of the game
	} return instance;
}

bool Game::save_player(Player*& p) {
	const std::string file_name = "game_save_file.txt"; // Constant load file path (eliminates user error)

	std::string name, location;
	int hp, maxHp, strength;

	std::ofstream outFile(file_name);

	if (!outFile) {
		std::cerr << "Error opening file: " << file_name << '\n';
		return false;
	}

	outFile << p->getName() << '\n';
	outFile << p->getHealth() << '\n';
	outFile << p->getMaxHealth() << '\n';
	outFile << p->getlevel() << '\n';
	outFile << p->getExp() << '\n';
	outFile << p->getStrength() << '\n';
	outFile << p->location << '\n';
	return true;
}

void Game::start(Player* p) {
	std::string start;
	std::cout << "\033[3J\033[H\033[2J"; //Control sequence to clear terminal
	std::cout << "\n\tWelcome, Adventurer " << p->getName() << "!\n";
	std::cout << "\t  --Entering the " << p->location << "--\n";
		
	std::cout << "\n\t>> Press enter to start <<";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //claer input stream
	std::getline(std::cin, start); //return when new line (enter is recived)
	return;
}

void Game::run(Game* g, Player* p) {
	start(p);
	save_player(p);
	Player_Menu(p);

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
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //claer input stream
	std::getline(std::cin, input); //return when new line (enter is recived)
	return;
}

void Game::Player_Menu(Player* p) {

	int choice;
	bool quit = false;

	do {
		std::cout << "\033[3J\033[H\033[2J"; //Control sequence to clear terminal
		std::cout << "\n\n==============================\n";
		std::cout << "\tPlayer Menue\t";
		std::cout << "\n==============================\n";

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
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input stream
			}

		} while (choice < 1 || choice > 6);

		switch (choice) {
		case 1:
			std::cout << "\033[3J\033[H\033[2J"; //Control sequence to clear terminal
			std::cout << "\n\n--- PLAYER STATS ---\n";
			p->to_string();
			ask_to_continue();
			break;

		case 5:
			std::cout << "\033[3J\033[H\033[2J"; //Control sequence to clear terminal
			save_player(p);
			std::cout << "\t>> Game saved <<\n";
			ask_to_continue();
			break;
		case 6:
			quit = quit_game();
			break;
		default:
			std::cout << "Not implemneted yet :/";

		};

	} while (quit == false);
}