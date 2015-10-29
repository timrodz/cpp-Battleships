//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2005 - 2015 Media Design School
// 
// File name   : Screen.cpp
// Description : General purpose functions
// Author      : Juan Rodriguez
// Mail        : juan.rod6618@mediadesignschool.com
// 

// Library includes
#include <conio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>

// Cancelling input
#define CANCEL -1

// Local includes
#include "Screen.h"

// Defining our console handle, cursor position and coordinates to position the cursor to
HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cursor;
COORD coord;

// Going to a desired position in the screen
// SCREEN DIMENSIONS: 80 wide by 24 tall
// Optional: can hide the cursor
void gotoxy(int x, int y, bool hideCursor) {
	if (hideCursor == true) {
		cursor.bVisible = false;
		cursor.dwSize = 1;
	}
	else {
		cursor.bVisible = true;
		cursor.dwSize = 20;
	}
	std::cout.flush();
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorInfo(consoleHandle, &cursor);
	SetConsoleCursorPosition(consoleHandle, coord);
}

// Setting the color for our screen
void setColor(Color c) {
	SetConsoleTextAttribute(consoleHandle, c);
}

// Clearing the console on the right side of the screen
void clearInput(int x, int yMin, int yMax) {
	for (int i = x; i < 80; ++i) {
		for (int j = yMin; j <= yMax; ++j) {
			print(i, j, " ");
		}
	}
	gotoxy(x, 0, true);
}

/// Reading strings
// String to Int with Comparison
int stringToInt(std::string& inputSort, // String to read
	std::string phrase,                 // Text to display when errors occur
	Comparison comp,                    // Type of comparison
	int minValue, int maxValue,         // range of comparison
	int x, int y,                       // coordinates to print
	int xOffset, int yOffset) {         // Offsets for printing (when errors occur)

	int numberToCompare;

	while (true) {
		// Accessing the string value of a stringstream is done by calling the 'str' method
		std::stringstream ss(readLimitedInput(x, y));
		setColor(WHITE);
		if (ss.str() == "~/.") {
			return CANCEL;
		}
		// string stream to integer shift
		if (ss >> numberToCompare) {
			switch (comp) {
			// Equal
			case eq:
				if ((numberToCompare == minValue) || (numberToCompare == maxValue)) {
					return numberToCompare;
				}
				break;
			// Between
			case btw:
				if ((numberToCompare >= minValue) || (numberToCompare <= maxValue)) {
					return numberToCompare;
				}
				break;
			// Between not included both
			case btwNIB:
				if ((numberToCompare > minValue) || (numberToCompare < maxValue)) {
					return numberToCompare;
				}
				break;
			// Between not included left
			case btwNIL:
				if ((numberToCompare > minValue) || (numberToCompare <= maxValue)) {
					return numberToCompare;
				}
				break;
			// Between not included right
			case btwNIR:
				if ((numberToCompare >= minValue) || (numberToCompare < maxValue)) {
					return numberToCompare;
				}
				break;
			// Outside
			case out:
				if (!(numberToCompare <= minValue) || (numberToCompare >= maxValue)) {
					return numberToCompare;
				}
				break;
			// Outside not included both
			case outNIB:
				if (!(numberToCompare < minValue) || (numberToCompare > maxValue)) {
					return numberToCompare;
				}
				break;
			// Outside not included left
			case outNIL:
				if (!(numberToCompare < minValue) || (numberToCompare >= maxValue)) {
					return numberToCompare;
				}
				break;
			// Outside not included right
			case outNIR:
				if (!(numberToCompare <= minValue) || (numberToCompare > maxValue)) {
					return numberToCompare;
				}
				break;
			} // switch end
			print(x, y, " ");
			print(x - xOffset, y + yOffset, phrase);
		}
		else {
			print(x, y, " ");
			print(x - xOffset, y + yOffset, phrase);
		}
	} // while end
}

/// Printing strings
void print(int x, int y, Color stringColor, std::string s) {
	setColor(stringColor);
	gotoxy(x, y, true);
	std::cout << s;
	setColor(WHITE);
}

void print(int x, int y, std::string s) {
	gotoxy(x, y, true);
	std::cout << s;
}

void print(Color stringColor, std::string s) {
	setColor(stringColor);
	std::cout << s;
	setColor(WHITE);
}

/// Printing characters
void print(int x, int y, Color charColor, char c) {
	setColor(charColor);
	gotoxy(x, y, true);
	std::cout << c;
	setColor(WHITE);
}

void print(int x, int y, char c) {
	gotoxy(x, y, true);
	std::cout << c;
}

void print(Color charColor, char c) {
	setColor(charColor);
	std::cout << c;
	setColor(WHITE);
}

/// Printing integers
void print(int x, int y, int number) {
	gotoxy(x, y, true);
	std::cout << number;
}

// Limiting the input to only one character
std::string readLimitedInput(int x, int y) {
	// Limit of characters
	const int LIMIT = 1;
	// counter of characters
	int stringIndex = 0;
	// Our string to return
	std::string stringToAppend;
	// Our character that we'll append to 's'
	char charToRead;
	while (true) {
		gotoxy(x, y, false);
		charToRead = _getch();
		// We make sure we've more than 0 letters 
		// (otherwise we'll be popping the string at index -1)
		if ((charToRead == 8) && (stringIndex > 0)) {
			stringToAppend.pop_back();
			// Iterate back to our last position
			stringIndex--;
			x--;
			print(x, y, " ");
		}
		else if ((charToRead == 8) && (stringIndex == 0)) {
			// Nothing happens (on purpose)
		}
		else {
			// This limits the amount of characters that
			// our input can receive (change 1 to desired limit)
			if (stringIndex != LIMIT) {
				
				// we push our character into our stack
				stringToAppend.push_back(charToRead);
				stringIndex++;
				x++;
				// Uppercase conversion
				// We do this for every non-digit using the isdigit(std::string) function
				// index - 1 because arrays are counted starting from 0, otherwise we can just use 'index'
				if ( !( isdigit( stringToAppend[stringIndex] ) ) ) {
					stringToAppend[stringIndex - 1] = toupper(stringToAppend[stringIndex - 1]);
				}

			}
		}
		gotoxy(x - 1, y, false);
		if (stringIndex - 1 != -1) {
			setColor(PINK);
			std::cout << stringToAppend[stringIndex - 1];
		}

		if (charToRead == 13) {
			//Beep(750, 100);
			return stringToAppend;
		}
		else if (charToRead == 27) {
			return "~/.";
		}
	}
}

// Alternative to system("pause");
void confirmRETURN(int x, int y) {
	print(x, y, WHITE, "Press ");
	print(GREEN, "ENTER / RETURN");
	print(WHITE, " to continue> ");
	while (true) {
		if (_getch() == 13) {
			break;
		}
	}
}