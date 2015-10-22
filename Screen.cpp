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

// Local includes
#include "Screen.h"

HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

void gotoxy(int x, int y) {
	//CONSOLE_CURSOR_INFO lpCursor;
	
	//lpCursor.bVisible = false;
	//lpCursor.dwSize = 1;
	std::cout.flush();
	coord.X = x;
	coord.Y = y;
	//SetConsoleCursorInfo(consoleHandle, &lpCursor);
	SetConsoleCursorPosition(consoleHandle, coord);
}

void setColor(Color c) {
	SetConsoleTextAttribute(consoleHandle, c);
}

void clearInput(int x) {
	for (int i = x; i < 80; ++i) {
		for (int j = 0; j <= 24; ++j) {
			gotoxy(i, j);
			std::cout << " ";
		}
	}
}

/// Reading strings
// String to Int with Comparison
int stringToIntComp(std::string input,
	std::string phrase,
	Comparison comp,
	int min, int max,
	int x, int y,
	int xOffset, int yOffset) {
	// Number to compare
	int i;
	while (true) {
		std::stringstream ss(readLimitedInput(x, y));
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

// String
void read(std::string s, std::string phrase, int x, int y, Color stringColor) {

}

/// Reading Characters
void read(char c, std::string phrase, int x, int y, Color charColor) {
	
}

void read(char c, std::string phrase, int x, int y) {

}

// Printing strings
void print(int x, int y, Color stringColor, std::string s) {
	setColor(stringColor);
	gotoxy(x, y);
	std::cout << s;
	setColor(WHITE);
}

void print(int x, int y, std::string s) {
	gotoxy(x, y);
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
	gotoxy(x, y);
	std::cout << c;
	setColor(WHITE);
}

void print(int x, int y, char c) {
	gotoxy(x, y);
	std::cout << c;
}

void print(Color charColor, char c) {
	setColor(charColor);
	std::cout << c;
	setColor(WHITE);
}

// Printing integers
void print(int x, int y, int number) {
	gotoxy(x, y);
	std::cout << number;
}

// Limiting the input to only one character
std::string readLimitedInput(int x, int y) {
	// Limit of characters
	const int LIMIT = 1;
	// counter of characters
	int index = 0;
	// Our string to return
	std::string s;
	// Our character that we'll append to 's'
	char c;
	while (true) {
		gotoxy(x, y);
		c = _getch();
		// We make sure we've more than 0 letters 
		// (otherwise we'll be popping the string at index -1)
		if (c == 8 && index > 0) {
			s.pop_back();
			// Iterate back to our last position
			index--;
			x--;
			print(x, y, " ");
		}
		else if (c == 8 && index == 0) {
			// Nothing happens (on purpose)
		}
		else {
			// This limits the amount of characters that
			// our input can receive (change 1 to desired limit)
			if (index != LIMIT) {
				// we push our character into our stack
				s.push_back(c);
				index++;
				x++;
				// Uppercase conversion
				// We do this for every non-digit using the isdigit(std::string) function
				// index - 1 because arrays are counted starting from 0, otherwise we can just use 'index'
				if (! (isdigit( s[index]) ) ) {
					s[index - 1] = toupper(s[index - 1]);
				}
			}
		}
		gotoxy(x-1, y);
		if (index - 1 != -1) {
			std::cout << s[index - 1];
		}
		
		if (c == 13) {
			return s;
		}
	}
}