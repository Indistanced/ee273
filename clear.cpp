//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 17/03/2026

//Changes made:
//-Add in ask_to_continue() function to provent repetition within code

#include "clear.h"
#include <limits>

// Clear any error flags on the input stream and removes leftover input
void clearBuffer() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input stream
}

// Clear the terminal screen
void terminateBuffer() {
	std::cout << "\033[3J\033[H\033[2J"; // Control sequence to clear  
}

// Pause the program until the user presses Enter
void ask_to_continue() {
	std::cout << "\n>> Press enter to continue <<";
	std::cin.get();
	return;
}