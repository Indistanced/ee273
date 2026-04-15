#pragma once

#include <Windows.h>
#include <string>
#include "enemy.h"

void unicode_init();

void xbar(int size = 50);
void xdbar(int size);
void enbox(std::string text);

void create_slime(Enemy* e);
void create_goblin(Enemy* e);
void create_fire_spirit(Enemy* e);