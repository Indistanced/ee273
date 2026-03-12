#include <iostream> // Read and write functionality with console
#include <fstream> // Read and write functionality with files

#include "Player.h"
#include "menu.h"
#include "main.h"

bool Game::save_player(Player*& p) {
	const std::string file_name = "game_save_file.txt"; // Constant load file path (eliminates user error)

	std::string name, location;
	int hp, maxHp, strength;

	std::ofstream outFile(file_name);

	if (!outFile) {
		std::cerr << "Error opening file: " << file_name << '\n';
		return -1;
	}

	outFile << p->getName() << '\n';
	outFile << p->getHealth() << '\n';
	outFile << p->getMaxHealth() << '\n';
	outFile << p->getStrength() << '\n';
	outFile << p->location << '\n';
}

Game* Game::instance = nullptr; // Tells class that the game initially hasn't been created

Game* Game::getInstance(Player* p) {
	if (instance == nullptr) { // If game hasn't been created yet
		instance = new Game(p); // Create an instance of the game
	} return instance;
}

void Game::start(Player* p) {
	gout() << "Welcome, " << p->getName() << '\n';
	gout() << "Health: (" << p->getHealth() << "/" << p->getMaxHealth() << ")\n"; // Health bar check
	gout() << "Location: " << p->location << '\n';
}

void Game::run(Game* g, Player* p) {
	start(p);
	save_player(p);

	gout() << "What is your favourite number?\n"; // gout = cout (Game class)
	int num;
	Player::pin(p) >> num; // pin = cin (Player class)
}

std::ostream& Game::gout() {
	return std::cout << ">> ";
}

int main() {
	Player* p1 = selectPlayerInstance(p1);
	if (p1 == nullptr) return 0; // Checks whether player exists

	Game* g = Game::getInstance(p1); // Creates, loads, or exits instance
	g->run(g, p1);

	delete p1;
	delete g;

	return 0;
}