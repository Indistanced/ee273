//Author: Aidan Kelly
//Creation Date: 20/04/26

//Changes made:
//- Create Minimap class

#pragma once

#include "clear.h"
#include "unicode.h"
#include "main.h"
#include "Player.h"

#include <Windows.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

// Allow only one Minimap instance to exist at once
class Minimap {
public:
	static void mapLoop();

	Minimap(const Minimap&) = delete;
	Minimap& operator=(const Minimap&) = delete;
};