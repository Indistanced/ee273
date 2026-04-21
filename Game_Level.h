//Author: Aidan Kelly
//Creation Date: 

//Changes made:

#pragma once

#include <map>
#include <string>
#include <array>

class Level {
public:
	// INITIALISATIONS
	static constexpr std::size_t NUMBER_OF_LEVELS = 3;

	static Level& getInstance() {
		static Level instance;
		return instance;
	}

	// ENFORCE SINGLE INSTANCE

	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;

	// MAIN
	static int test();

	inline static std::map<std::string, int> names = { {"Green Hill Zone", 1 }, {"Magic Mountain", 2}, {"The Arm of Dismay", 3} };

	inline static std::array<bool, NUMBER_OF_LEVELS> isComplete{ false };
	void isCompleteString();

private:
	Level() = default;
};