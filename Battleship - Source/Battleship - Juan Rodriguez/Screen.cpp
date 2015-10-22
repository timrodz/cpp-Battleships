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
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <conio.h>

// FLAGS
#define CANCEL -1

// Local includes
#include "Screen.h"

HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cursor;
COORD coord;

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

void setColor(Color c) {
	SetConsoleTextAttribute(consoleHandle, c);
}

void clearText(int x) {
	for (int i = x; i < 80; ++i) {
		for (int j = 0; j <= 24; ++j) {
			gotoxy(i, j, true);
			std::cout << " ";
		}
	}
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
		if (charToRead == 8 && stringIndex > 0) {
			stringToAppend.pop_back();
			// Iterate back to our last position
			stringIndex--;
			x--;
			print(x, y, " ");
		}
		else if (charToRead == 8 && stringIndex == 0) {
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
				if (!(isdigit(stringToAppend[stringIndex]))) {
					stringToAppend[stringIndex - 1] = toupper(stringToAppend[stringIndex - 1]);
				}
			}
		}
		gotoxy(x - 1, y, false);
		if (stringIndex - 1 != -1) {
			std::cout << stringToAppend[stringIndex - 1];
		}

		if (charToRead == 13) {
			return stringToAppend;
		}
		else if (charToRead == 27) {
			return "CANCEL";
		}
	}
}

/// Reading strings
// String to Int with Comparison
int stringToInt(std::string& inputSort,
	std::string phrase,
	Comparison comp,
	int min, int max,
	int x, int y,
	int xOffset, int yOffset) {
	// Number to compare
	int i;
	while (true) {
		std::stringstream ss(readLimitedInput(x, y));
		if (ss.str() == "CANCEL") {
			return CANCEL;
		}
		if (ss >> i) {
			switch (comp) {
			case eq:
				if (i == min || i == max) {
					return i;
				}
				break;
			case btw:
				if (i >= min || i <= max) {
					return i;
				}
				break;
			case btwNIB:
				if (i > min || i < max) {
					return i;
				}
				break;
			case btwNIL:
				if (i > min || i <= max) {
					return i;
				}
				break;
			case btwNIR:
				if (i >= min || i < max) {
					return i;
				}
				break;
			case out:
				if (!(i <= min || i >= max)) {
					return i;
				}
				break;
			case outNIB:
				if (!(i < min || i > max)) {
					return i;
				}
				break;
			case outNIL:
				if (!(i < min || i >= max)) {
					return i;
				}
				break;
			case outNIR:
				if (!(i <= min || i > max)) {
					return i;
				}
				break;
			}
			print(x, y, " ");
			print(x - xOffset, y + yOffset, phrase);
		}
		else {
			print(x, y, " ");
			print(x - xOffset, y + yOffset, phrase);
		}
	}
}

// Printing strings
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

// Printing characters
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

// Printing integers
void print(int x, int y, int number) {
	gotoxy(x, y, true);
	std::cout << number;
}