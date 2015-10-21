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

// 16 Bit color palette (used in the 'setColor' function)
enum Color {
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

// Going to a desired position in the screen
// SCREEN DIMENSIONS: 80 wide by 24 tall
// Optional: can hide the cursor
void gotoxy(int x, int y);

// Setting the color for our screen
void setColor(Color c);

// Clearing the console on the right side of the screen
void clearInput(int x);

enum Comparison {
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

// - String to int conversion (and comparison between a range) -
// input - string to read
// phrase - text to display when errors happen
// comparisonType:
// -> eq: equal                                (== || ==)
// -> btw: between                             (>= || <=)
// -> btwNIB: between not including both sides (>  ||  <)
// -> btwNIL: between not including LEFT side  (>  || <=)
// -> btwNIR: between not including RIGHT side (>= ||  <)
// -> out: outside of the range                (<= || >=)
// -> outNIB: outside not including both sides (<  ||  >)
// -> outNIL: outside not including LEFT side  (<  || >=)
// -> outNIR: outside not including RIGHT side (<= ||  >)
//
// ******************************************************
// Other parameters
// min - minimum value to check
// max - maximum value to check
// x, y - coordinates to print
// xOffset, yOffset - coordinates to print with offset (when errors happen)
int stringToIntComp(std::string input, 
				std::string phrase, 
				Comparison comp, 
				int min, int max, 
				int x, int y, 
				int xOffset, int yOffset);

// Reading a string/character
void read(std::string s, std::string phrase, int x, int y, Color stringColor);
void read(char c, std::string phrase, int x, int y, Color charColor);
void read(char c, std::string phrase, int x, int y);

// Printing a string/character
void print(int x, int y, Color stringColor, std::string s);
void print(int x, int y, std::string s);
void print(Color stringColor, std::string s);
void print(int x, int y, Color charColor, char c);
void print(int x, int y, char c);
void print(Color charColor, char c);
void print(int x, int y, int number);

// Limits the input to only one character
std::string readLimitedInput(int x, int y);
#endif /* Screen.h */