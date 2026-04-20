//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 01/03/26

//Changes made:
//- added in random number generator seed
//- added unicode enable  

#include "Player.h"
#include "menu.h"
#include "Game.h"
#include "unicode.h"
#include "Game_Level.h"
#include "main.h"

#include <thread>
#include <ctime>

#include <Windows.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

bool running = true;

void mapWindow(Player*& p) {
	if (!p) return;

	static std::unordered_map<std::string, cv::Mat> maps = {
		{"town", cv::imread("D:\\repos\\ee273\\town_img.png")},
		{"green hill zone", cv::imread("D:\\repos\\ee273\\ghz_img.png") },
		{"magic mountain", cv::imread("D:\\repos\\ee273\\mm_img.png") },
		{"the arm of dismay", cv::imread("D:\\repos\\ee273\\taos_img.png")},
		{"end", cv::imread("D:\\repos\\ee273\\end_img.png") }
	};
	

	static bool initialised = false;
	if (!initialised) {
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);
		int windowSize = 300;

		int x = (screenWidth - windowSize) / 2;
		int y = (screenHeight - windowSize) / 2;

		cv::namedWindow("Map", cv::WINDOW_NORMAL);
		cv::resizeWindow("Map", 300, 300);
		cv::moveWindow("Map", x, y);

		initialised = true;
	}

	std::string currentLoc = p->getLocation();
	static std::string lastLoc = "";

	if (maps.find(p->getLocation()) != maps.end()){
		if (currentLoc != lastLoc) {
			cv::imshow("Map", maps[currentLoc]);
			cv::waitKey(1);
			lastLoc = currentLoc;
		}
		
	}
}

int gameLoop() {
	while (running) {
		Player* p = nullptr;
		p = selectPlayerInstance(p);
		if (p == nullptr) {
			return 0; // Check whether player exists
		}

		Game* g = Game::getInstance(p); // Create, load, or exit instance
		bool alive = g->run(g, p);



		// TESTING
		Level::test();

		delete g;
		Game::resetInstance();
		if (!p->isAlive()) {
			if (gameOverMenu(p)) { // If RESTART
				delete p;
				continue;
			}
			else { // IF EXIT GAME
				running = false;
				delete p;
				return 0;
			}
		} delete p;
	}
}

void mapLoop() {
	cv::Mat img = cv::imread("D:\\repos\\ee273\\town_img.png");
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int windowSize = 300;

	int x = (screenWidth - windowSize) / 2;
	int y = (screenHeight - windowSize) / 2;

	cv::namedWindow("Map", cv::WINDOW_NORMAL);
	cv::resizeWindow("Map", 300, 300);
	cv::moveWindow("Map", x, y);
	cv::imshow("Map", img);

	while (running) cv::waitKey(1);
}



int main() {
	// INITIALISATIONS;
	srand(static_cast<unsigned int>(time(0))); // Random number generator set seed
	unicode_init(); // Enable unicode
	
	std::thread t1(gameLoop);
	std::thread t2(mapLoop);

	t1.join();
	t2.join();
}

