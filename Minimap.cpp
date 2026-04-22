#include "Minimap.h"
#include <array>
#include <map>
#include <Windows.h>
#include <unordered_map>

void Minimap::mapLoop() {
	std::array level_names = { "Town", "Green Hill Zone", "Magic Mountain", "The Arm of Dismay", "End" };

	static std::unordered_map<std::string, cv::Mat> maps = {
		{"Town", cv::imread("town_img.png")},
		{"Green Hill Zone", cv::imread("ghz_img.png") },
		{"Magic Mountain", cv::imread("mm_img.png") },
		{"The Arm of Dismay", cv::imread("taos_img.png")},
		{"End", cv::imread("end_img.png") }
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
		cv::imshow("Map", maps[level_names[0]]);

		initialised = true;
	}

	while (running) {
		if (p == nullptr) {
			cv::waitKey(1);
			continue;
		}

		for (int i{}; i < level_names.size(); i++) {
			if (p->getLocation() == level_names[i]) {
				cv::imshow("Map", maps[level_names[i]]);
				cv::waitKey(1);
			}
		}
	}
}