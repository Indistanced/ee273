//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 17/03/2026 

//Changes made:
//- Add in ask_to_continue() declaration

#pragma once

#include <iostream>

void clearBuffer(); // Clears the input stream to prevent leftover or invalid input from affecting cin operations
void terminateBuffer(); // Clears terminal screen
void ask_to_continue(); // Pauses program until the user presses enter