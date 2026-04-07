#pragma once

#include <Windows.h>
#include <string>

void unicode_init();

void xbar(int size = 50);
void xdbar(int size);
void enbox(std::string text);

void create_slime();