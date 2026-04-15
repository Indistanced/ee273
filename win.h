#pragma once

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMinimap();
int DisplayMinimap();