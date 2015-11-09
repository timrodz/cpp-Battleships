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

// Local includes
#include "Screen.h"

// Defining our console handle, cursor position and coordinates to position the cursor to
HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cursor;
COORD coord;

// Going to a desired position in the screen and hiding the cursor if desired
// @param _iX the 'x' coordinate to print at
// @param _iY the 'y' coordinate to print at
// @param _bHideCursor true for hiding, false for showing
// @return void
void gotoxy(int _iX, int _iY, bool _bHideCursor) {

	if (_bHideCursor == true) {

		cursor.bVisible = false;
		cursor.dwSize = 1;

	}
	else {

		cursor.bVisible = true;
		cursor.dwSize = 20;

	}
	std::cout.flush();
	coord.X = _iX;
	coord.Y = _iY;
	SetConsoleCursorInfo(consoleHandle, &cursor);
	SetConsoleCursorPosition(consoleHandle, coord);

}

// Setting the color for our screen
// @param _color the color code
// @return void
void setColor(eColor _eColor) {

	SetConsoleTextAttribute(consoleHandle, _eColor);

}

// Clearing the console on the right side of the screen
// @param _iX the 'x' coordinate to print at
// @param _iYmin the minimum 'y' position to start clearing
// @param _iYmax the maximum 'y' position to stop clearing at
// @return void
void clearInput(int _iX, int _iYmin, int _iYmax) {

	for (int i = _iX; i < 80; ++i) {

		for (int j = _iYmin; j <= _iYmax; ++j) {

			print(i, j, " ");

		}

	}

	gotoxy(_iX, 0, true);

}

/// Reading strings
// String to Int with Comparison
// @param _rStrInput the string to read
// @param _strPhrase the phrase to display if an error occurs
// @param _eComp the type of comparison to make
// @param _iMinValue the minimum value to compare
// @param _iMaxValue the maximum value to compare
// @param _iX the 'x' coordinate to print at
// @param _iY the 'y' coordinate to print at
// @param _iXoffset the 'x' offset to clear the previous text
// @param _iYoffset the 'y' offset to display the error text (_strPhrase)
int stringToInt(std::string& _rStrInput, std::string _strPhrase, eComparison _eComp,
	int _iMinValue, int _iMaxValue, int _iX, int _iY, int _iXoffset, int _iYoffset) {

	int iNumberToCompare;

	while (true) {
		// Accessing the string value of a stringstream is done by calling the 'str' method
		std::stringstream ss(readLimitedInput(_iX, _iY));
		setColor(WHITE);
		if (ss.str() == "~/.") {

			return CANCEL;

		}
		// string stream to integer shift
		if (ss >> iNumberToCompare) {
			switch (_eComp) {
				// Equal
			case eq:
				if ((iNumberToCompare == _iMinValue) || (iNumberToCompare == _iMaxValue)) {

					return iNumberToCompare;

				}
				break;
				// Between
			case btw:
				if ((iNumberToCompare >= _iMinValue) || (iNumberToCompare <= _iMaxValue)) {

					return iNumberToCompare;

				}
				break;
				// Between not included both
			case btwNIB:
				if ((iNumberToCompare > _iMinValue) || (iNumberToCompare < _iMaxValue)) {

					return iNumberToCompare;

				}
				break;
				// Between not included left
			case btwNIL:
				if ((iNumberToCompare > _iMinValue) || (iNumberToCompare <= _iMaxValue)) {

					return iNumberToCompare;

				}
				break;
				// Between not included right
			case btwNIR:
				if ((iNumberToCompare >= _iMinValue) || (iNumberToCompare < _iMaxValue)) {

					return iNumberToCompare;

				}
				break;
				// Outside
			case out:
				if (!(iNumberToCompare <= _iMinValue) || (iNumberToCompare >= _iMaxValue)) {

					return iNumberToCompare;

				}
				break;
				// Outside not included both
			case outNIB:
				if (!(iNumberToCompare < _iMinValue) || (iNumberToCompare > _iMaxValue)) {

					return iNumberToCompare;

				}
				break;
				// Outside not included left
			case outNIL:
				if (!(iNumberToCompare < _iMinValue) || (iNumberToCompare >= _iMaxValue)) {

					return iNumberToCompare;

				}
				break;
				// Outside not included right
			case outNIR:
				if (!(iNumberToCompare <= _iMinValue) || (iNumberToCompare > _iMaxValue)) {

					return iNumberToCompare;

				}

				break;

			} // switch end

			print(_iX, _iY, " ");
			print(_iX - _iXoffset, _iY + _iYoffset, _strPhrase);

		}
		else {

			print(_iX, _iY, " ");
			print(_iX - _iXoffset, _iY + _iYoffset, _strPhrase);

		}

	} // while end

}

// Limiting the input to only one character
// @param _iX the 'x' coordinate to print at
// @param _iY the 'y' coordinate to print at
// @return void
std::string readLimitedInput(int _iX, int _iY) {

	// Limit of characters
	const int LIMIT = 1;
	// counter of characters
	int stringIndex = 0;
	// Our string to return
	std::string stringToAppend;
	// Our character that we'll append to 's'
	char charToRead;
	while (true) {

		gotoxy(_iX, _iY, false);
		charToRead = _getch();
		// We make sure we've more than 0 letters 
		// (otherwise we'll be popping the string at index -1)
		if ((charToRead == 8) && (stringIndex > 0)) {

			stringToAppend.pop_back();
			// Iterate back to our last position
			stringIndex--;
			_iX--;
			print(_iX, _iY, " ");

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
				_iX++;
				// Uppercase conversion
				// We do this for every non-digit using the isdigit(std::string) function
				// index - 1 because arrays are counted starting from 0, otherwise we can just use 'index'
				if (!(isdigit(stringToAppend[stringIndex]))) {

					stringToAppend[stringIndex - 1] = toupper(stringToAppend[stringIndex - 1]);

				}

			}

		}
		gotoxy(_iX - 1, _iY, false);
		if (stringIndex - 1 != -1) {

			setColor(PINK);
			std::cout << stringToAppend[stringIndex - 1];

		}

		if (charToRead == 13) {

			return stringToAppend;

		}
		else if (charToRead == 27) {

			return "~/.";

		}

	}

}

// Prompts for confirmation
// @param _iX the 'x' coordinate to print at
// @param _iY the 'y' coordinate to print at
// @return void
void confirmRETURN(int _iX, int _iY) {

	print(_iX, _iY, WHITE, "Press ");
	print(GREEN, "ENTER / RETURN");
	print(WHITE, " to continue> ");
	while (true) {

		if (_getch() == 13) {

			break;

		}

	}

}

///////////////////////////////////////////////////////////////////////////
// Since the next functions are just for printing,                       //
// The arguments are the same through the overloads where they're found  //
// @param _iX the 'x' coordinate to print at                             //
// @param _iY the 'y' coordinate to print at                             //
// @param _eColor the color to set the text                              //
// @param _string the phrase to display                                  //
// @param _character the character to display                            //
// @param _int the integer to display                                    //
///////////////////////////////////////////////////////////////////////////

/// > Printing strings
void print(int _iX, int _iY, eColor _eColor, std::string _string) {

	setColor(_eColor);
	gotoxy(_iX, _iY, true);
	std::cout << _string;
	setColor(WHITE);

}

void print(int _iX, int _iY, std::string _string) {

	gotoxy(_iX, _iY, true);
	std::cout << _string;

}

void print(eColor _eColor, std::string _string) {

	setColor(_eColor);
	std::cout << _string;
	setColor(WHITE);

}

/// > Printing characters
void print(int _iX, int _iY, eColor _eColor, char _character) {

	setColor(_eColor);
	gotoxy(_iX, _iY, true);
	std::cout << _character;
	setColor(WHITE);

}

void print(int _iX, int _iY, char _character) {

	gotoxy(_iX, _iY, true);
	std::cout << _character;

}

void print(eColor _eColor, char _character) {

	setColor(_eColor);
	std::cout << _character;
	setColor(WHITE);

}

/// > Printing integers
void print(int _iX, int _iY, int _int) {

	gotoxy(_iX, _iY, true);
	std::cout << _int;

}