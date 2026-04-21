//Author: Aidan Kelly 
//Creation Date: 

//Changes made:

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

class Minimap {
public:
	static void mapLoop();

	// ENFORCE SINGLE INSTANCE

	Minimap(const Minimap&) = delete;
	Minimap& operator=(const Minimap&) = delete;
};