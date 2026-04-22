//Author: Aidan Kelly
//Creation Date: 20/04/26

//Changes made:
//- Use OpenCV for displaying images
//- Display static image concurrently with the game loop
//- Make the image shown depend on the level the user is at

#include "Minimap.h"
#include <array>
#include <map>
#include <Windows.h>
#include <unordered_map>

void Minimap::mapLoop() {
	std::array level_names = { "Town", "Green Hill Zone", "Magic Mountain", "The Arm of Dismay", "End" };

	static std::unordered_map<std::string, cv::Mat> maps = {
		{"Town", cv::imread("town.png")},
		{"Green Hill Zone", cv::imread("green_hill_zone.png") },
		{"Magic Mountain", cv::imread("magic_mountain.png") },
		{"The Arm of Dismay", cv::imread("the_arm_of_dismay.png")},
		{"End", cv::imread("end.png") }
	};

	static bool initialised = false;
	if (!initialised) { // Ensures the default window parameters are only defined once
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);
		int windowSize = 300;

		int x = (screenWidth - windowSize) / 2;
		int y = (screenHeight - windowSize) / 2;

		// Set default window parameters
		cv::namedWindow("Map", cv::WINDOW_NORMAL);
		cv::resizeWindow("Map", 300, 300);
		cv::moveWindow("Map", x, y);
		cv::imshow("Map", maps[level_names[0]]);

		initialised = true;
	}

	while (running) {
		if (p == nullptr) {
			cv::waitKey(1);
			continue;
		}

		// Image shown corresponds with player level
		for (int i{}; i < level_names.size(); i++) {
			if (p->getLocation() == level_names[i]) {
				cv::imshow("Map", maps[level_names[i]]);
				cv::waitKey(1);
			}
		}
	}
}