#include "unicode.h"
#include <iostream>
#include <string>

void unicode_init() {
	SetConsoleOutputCP(CP_UTF8);
}

void xbar(int size) {
	for (int i{}; i < size; i++) {
		std::cout << u8"─";
	}
}

void xdbar(int size) {
	for (int i{}; i < size; i++) {
		std::cout << u8"═";
	}
}

void enbox(std::string text) {
	std::cout << u8"┌"; xbar(text.size()); std::cout << u8"┐" << '\n';
	std::cout << u8"│" << text << u8"│" << '\n';
	std::cout << u8"└"; xbar(text.size()); std::cout << u8"┘";
}

void create_slime() {
	std::cout << "HP: [TBD/TBD]\n";
	std::cout << u8"┌"; xbar(19); std::cout << u8"┐" << '\n';
	std::cout << u8"│   ┌"; xbar(3); std::cout << u8"┐" << u8"   ┌"; xbar(3); std::cout << u8"┐   │" << '\n';
	std::cout << u8"│   │" << " O " << u8"│" << u8"   │" << " O " << u8"│   │" << '\n';
	std::cout << u8"│   └"; xbar(3); std::cout << u8"┘" << u8"   └"; xbar(3); std::cout << u8"┘   │" << '\n';
	std::cout << u8"│                   │\n";
	std::cout << u8"│                   │\n";
	std::cout << u8"└"; xbar(19); std::cout << u8"┘" << '\n';
	std::cout << u8"────────────────────────────────────────┬┬┬┐                                          ┌────────────────────────\n";
	std::cout << u8"                                         └────────────────────────────────────────────┴\n";
}