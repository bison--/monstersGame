#ifndef HELPER_H
#define HELPER_H

#include <iostream>

static void clearScreen()
{ 
	std::cout << "\033[2J";   // CLEAR screen!
	std::cout << "\033[1;1H"; // set coursor upper-left
}

#endif
