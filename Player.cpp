//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 02/03/26

//Changes made:
//- added in Level and experience functions
//- added in quest management functions

#include "player.h"
#include "unicode.h"

#include <fstream>
#include <iostream>

std::istream& Player::pin(Player* p) {
	std::cout << p->getName() << ": ";
	return std::cin;
}

//Player stats to string
void Player::to_string() {

	std::cout << "Name: " << this->name << "\n";
	std::cout << "Health: " << "(" << this->currentHealth << "/" << this->maxHealth << ")\n";
	std::cout << "Level: " << this->level << "\n";
	std::cout << "Exp: " << "(" << this->exp << "/" << this->expLimit << ")\n";
	std::cout << "Strength: " << this->strength << "\n";
	std::cout << "Location: " << this->location << "\n";
}

//add experience 
void Player::addExp(int exp_amount) {

	exp += exp_amount;

	//levelling up mechanic
	if (exp >= expLimit) {

		level++;
		exp = exp - expLimit;
		maxHealth += 20;
		strength += 5;
		currentHealth = maxHealth;
		expLimit += 50;

		dashText("YOU LEVELED UP!");
		std::cout << "-New Health: " << maxHealth <<"\n";
		std::cout << "-New Strength: " << strength << "\n";
	}
}

std::ostream& Player::pout(Player* p) {
	return std::cout << p->getName() << ": ";
}


std::vector<std::pair<std::string, bool>>& Player::getQuests() {
	return quests;
}

bool Player::addQuest(std::string description, bool complete) {

	//check to make sure quest is not added twice
	for (auto& q : quests) {
		if (q.first == description) {
			return false;
		}
	}

	quests.push_back(std::make_pair(description, complete));
	return true;
}

bool Player::completeQuest(std::string description) {
	for (int i = 0; i < quests.size(); i++) {
		if (quests[i].first == description) {
			quests[i].second = true;
			return true;
		}
	}

	return false;
}

void Player::quests_to_string() {
	for (int i = 0; i < quests.size(); i++) {
		std::cout << quests[i].first << " | ";

		if (quests[i].second) {
			std::cout << "Complete\n";
		}
		else {
			std::cout << "Incomplete\n";
		}
	}
}

int Player::questNumber() {
	return (int)quests.size();
}