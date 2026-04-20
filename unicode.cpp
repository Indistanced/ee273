#include "unicode.h"
#include <iostream>
#include <string>

void unicode_init() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
}

void xbar(int size) {
	for (int i{}; i < size; i++) {
		std::cout << "─";
	}
}

void xdbar(int size) {
	for (int i{}; i < size; i++) {
		std::cout << "═";
	}
}

void enbox(std::string text) {
	std::cout << "┌"; xbar(text.size()); std::cout << "┐" << '\n';
	std::cout << "│" << text << "│" << '\n';
	std::cout << "└"; xbar(text.size()); std::cout << "┘";
}


void dashText(std::string text) {
	std::cout << "  ── " << text << " ──\n";
}