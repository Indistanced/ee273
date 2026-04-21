//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 

//Changes made:
//- added in dashText() fucntion to help reduce repatition.
//- added in unicode_init() to initilise Unicode

#include "unicode.h"
#include <iostream>
#include <string>

// Initialise to use UTF-8 encoding for proper Unicode output/input
void unicode_init() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
}

// Prints a single lined horizontal bar using Unicode characters
void xbar(int size) {
	for (int i{}; i < size; i++) {
		std::cout << "─";
	}
}

// Prints a double lined horizontal bar for stronger visual separation
void xdbar(int size) {
	for (int i{}; i < size; i++) {
		std::cout << "═";
	}
}

// Draws a box around the given text using Unicode characters
void enbox(std::string text) {
	std::cout << "┌"; xbar(text.size()); std::cout << "┐" << '\n';
	std::cout << "│" << text << "│" << '\n';
	std::cout << "└"; xbar(text.size()); std::cout << "┘";
}

// Displays text with dashes on either side
void dashText(std::string text) {
	std::cout << "  ── " << text << " ──\n";
}