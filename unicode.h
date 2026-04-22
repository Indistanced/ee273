//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 22/03/2026

//Changes made:
//- Add in dashText() function to help reduce repetition.
//- Add in unicode_init() to initialise Unicode

#pragma once

#include <Windows.h>
#include <string>

void unicode_init();

void xbar(int size = 50);
void xdbar(int size);
void enbox(std::string text);
void dashText(std::string text);