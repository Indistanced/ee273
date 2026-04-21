//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 

//Changes made:
//- added in dashText() fucntion to help reduce repatition.
//- added in unicode_init() to initilise Unicode

#pragma once

#include <Windows.h>
#include <string>

void unicode_init();

void xbar(int size = 50);
void xdbar(int size);
void enbox(std::string text);
void dashText(std::string text);