//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 

//Changes made:
//-Added in ask_to_continue() function to provent repetition within code

#include "clear.h"
#include <limits>

// Clears any error flags on the input stream and removes leftover input
void clearBuffer() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input stream
}

// Clears the terminal screen
void terminateBuffer() {
	std::cout << "\033[3J\033[H\033[2J"; // Control sequence to clear  
}

// Pauses the program until the user presses Enter
void ask_to_continue() {
	std::cout << "\n>> Press enter to continue <<";
	std::cin.get();
	return;
}