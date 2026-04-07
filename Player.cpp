#include "player.h"

#include <fstream>
#include <iostream>

std::istream& Player::pin(Player* p) {
	std::cout << p->getName() << ": ";
	return std::cin;
}

void Player::to_string() {

	std::cout << "Name: " << this->name << "\n";
	std::cout << "Health: " << "(" << this->currentHealth << "/" << this->maxHealth << ")\n";
	std::cout << "Level: " << this->level << "\n";
	std::cout << "Exp: " << "(" << this->exp << "/" << this->exp_limit << ")\n";
	std::cout << "Strength: " << this->strength << "\n";
	std::cout << "Location: " << this->location << "\n";

}

void Player::addExp(int exp_ammount) {

	exp += exp_ammount;

	if (exp >= exp_limit) {

		level++;
		exp = exp - exp_limit;
		maxHealth += 20;
		strength += 10;
		currentHealth = maxHealth;

		std::cout << "-- You leveled up! --\n";
	}
}


std::vector<std::pair<std::string, bool>>& Player::getQuests() {
	return quest;
}

bool Player::addQuest(std::string description, bool complete) {

	for (auto& q : quest) {
		if (q.first == description) {
			return false;
		}
	}
	
	quest.push_back(std::make_pair(description, complete));
	return true;
}

bool Player::completeQuest(std::string description) {
	for (int i = 0; i < quest.size(); i++) {
		if (quest[i].first == description) {
			quest[i].second = true;
			return true;
		}
	}

	return false;
}

void Player::quests_to_string() {
	for (int i = 0; i < quest.size(); i++) {
		std::cout << quest[i].first << '|';
		 
		if (quest[i].second) {
			std::cout << "Complete\n";
		}
		else {
			std::cout << "Incomplete\n";
		}
	}
}

int Player::questNumber() {	
	return (int)quest.size();
}