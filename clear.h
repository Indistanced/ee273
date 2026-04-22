//Author: Aidan Kelly and Kyle Simpson
//Creation Date: 

//Changes made:
//-Added in ask_to_continue() decloration

#pragma once

#include <iostream>

void clearBuffer(); // Clears the input stream to prevent leftover or invalid input from affecting cin operations
void terminateBuffer(); // Clears terminal screen
void ask_to_continue(); // Pauses program until the user pesses enter