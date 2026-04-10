#include "clear.h"

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input stream
}

void terminateBuffer() {
    std::cout << "\033[3J\033[H\033[2J"; // Control sequence to clear  
}

void ask_to_continue() {
	std::cout << "\n>> Press enter to continue <<";
	clearBuffer();
	std::cin.get();
	return;
}