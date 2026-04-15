#pragma once

#include "clear.h"
#include "unicode.h"

class Minimap {
public:
	static void drawMinimap(int x, int y);

	// ENFORCE SINGLE INSTANCE

	Minimap(const Minimap&) = delete;
	Minimap& operator=(const Minimap&) = delete;
};