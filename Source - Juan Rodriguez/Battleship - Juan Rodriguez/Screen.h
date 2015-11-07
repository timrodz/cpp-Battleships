//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2005 - 2015 Media Design School
// 
// File name   : Screen.h
// Description : Setting styles for the console (color, size, etc.)
// Author      : Juan Rodriguez
// Mail        : juan.rod6618@mediadesignschool.com
// 

#pragma once
#ifndef __SCREEN_H__
#define __SCREEN_H__

// cancel flag
const int CANCEL = -1;

// 16 Bit color palette (used in the 'setColor' function)
enum eColor {
	BLACK = 0,
	DARKBLUE = 1,
	DARKGREEN = 2,
	DARKTEAL = 3,
	DARKRED = 4,
	DARKPINK = 5,
	DARKYELLOW = 6,
	GRAY = 7,
	DARKGRAY = 8,
	BLUE = 9,
	GREEN = 10,
	TEAL = 11,
	RED = 12,
	PINK = 13,
	YELLOW = 14,
	WHITE = 15
};

// -> eq: equal                                (== || ==)
// -> btw: between                             (>= || <=)
// -> btwNIB: between not including both sides (>  ||  <)
// -> btwNIL: between not including LEFT side  (>  || <=)
// -> btwNIR: between not including RIGHT side (>= ||  <)
// -> out: outside of the range                (<= || >=)
// -> outNIB: outside not including both sides (<  ||  >)
// -> outNIL: outside not including LEFT side  (<  || >=)
// -> outNIR: outside not including RIGHT side (<= ||  >)
enum eComparison {
	eq,
	btw,
	btwNIB,
	btwNIL,
	btwNIR,
	out,
	outNIB,
	outNIL,
	outNIR
};

// Going to a desired position in the screen
// SCREEN DIMENSIONS: 80 wide by 24 tall
// Optional: can hide the cursor
void gotoxy(int _iX, int _iY, bool _bHideCursor);

// Setting the color for our screen
void setColor(eColor _eColor);

// Clearing the console on the right side of the screen
void clearInput(int _iX, int _iYmin, int _iYmax);

// String to Integer conversion
int stringToInt(std::string& _rStrInput, std::string _strPhrase, eComparison _eComp,
	int _iMinValue, int _iMaxValue, int _iX, int _iY, int _iXoffset, int _iYoffset);

// Limits the input to only one character
// by using the '_getch()' function
std::string readLimitedInput(int _iX, int _iY);

// Prompts for confirmation
void confirmRETURN(int _iX, int _iY);

// Printing a string/character (with overloading)
void print(int _iX, int _iY, eColor _eColor, std::string _string);
void print(int _iX, int _iY, std::string _string);
void print(eColor _eColor, std::string _string);
void print(int _iX, int _iY, eColor _eColor, char _character);
void print(int _iX, int _iY, char _character);
void print(eColor _eColor, char _character);
void print(int _iX, int _iY, int number);

#endif /* Screen.h */