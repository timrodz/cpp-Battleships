//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2005 - 2015 Media Design School
// 
// File name   : Game.cpp
// Description : This class contains the code for the actual game
// Author      : Juan Rodriguez
// Mail        : juan.rod6618@mediadesignschool.com
// 

// Library includes
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <windows.h>

// Local includes
#include "Game.h"
#include "Screen.h"
//#include "Ship.h"

// Scope renaming
using std::cout;
using std::cin;

// Static variables
const int Game::MAX_SHIPS = 5;
const std::string Game::availableShipsName[5] = {
	"Aircraft Carrier ",
	"Battleship       ",
	"Destroyer        ",
	"Submarine        ",
	"Patrol Boat      "
};

Game::Game() {
	spaceTaken = false;
	// Player ships
	availableShips[0] = 0;
	// Computer ships
	availableShips[1] = 0;
}

Game::~Game() {}

/// Accessor methods
void Game::setFirstRunValue(bool firstRunValue) {
	firstRun = firstRunValue;
}

bool Game::getFirstRunValue() const {
	return firstRun;
}

bool Game::getCancelSort() const {
	return cancelSort;
}

bool Game::canPlaceShips(int i) const {
	return (getDeployedShips(i) > 0);
}

int Game::getDeployedShips(int i) const {
	return MAX_SHIPS - availableShips[i];
}

void Game::setGrid() {
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; ++j) {
			grid[i][j] = 0;
			grid[11][j] = 1;
			grid[i][11] = 1;
			//gotoxy(i + 1, j + 1);
			//cout << grid[i][j];
		}
		cout << "\n";
	}
}

void Game::setAvailableShips() {
	playerShips = new int[5];
	computerShips = new int[5];
	for (int i = 0; i < 5; ++i) {
		playerShips[i] = 0;
		computerShips[i] = 0;
	}
}

// Prints the current ships in the right corner of the screen
void Game::printAvailableShips() {
	gotoxy(50, 0);
	cout << "Available ships (C to exit)";
	for (int i = 0; i < 5; ++i) {
		if (playerShips[i] == 0) {
			gotoxy(56, i+1);
			cout << i+1 << ") " << availableShipsName[i] << "(";
			setColor(GREEN);
			cout << getShipCode(i);
			setColor(WHITE);
			cout << ")";
		}
		else {
			gotoxy(56, i + 1);
			cout << i + 1<< ") ";
			setColor(RED);
			cout << "ALREADY TAKEN";
			setColor(WHITE);
		}
	}
}

// Getting the info of our selected ship
int Game::getShipSize(int shipCode) const {
	if (shipCode == 0) 
		return 5;
	else if (shipCode == 1)
		return 4;
	else if (shipCode == 2)
		return 3;
	else if (shipCode == 3)
		return 3;
	else if (shipCode == 4)
		return 2;
	else
		return 0;
}

char Game::getShipCode(int shipCode) const {
	if (shipCode == 0)
		return '@';
	else if (shipCode == 1)
		return '#';
	else if (shipCode == 2)
		return '&';
	else if (shipCode == 3)
		return '*';
	else if (shipCode == 4)
		return '$';
	else
		return '\0';
}

/// Render the screen
void Game::drawBattleScreen() {
	clearInput(42);
	// This will store our letters from A to J
	char letter = 'A';
	print(8, 0, WHITE, "Player");
	setColor(TEAL);
	for (int i = 0; i <= 10; ++i) {
		for (int j = 0; j <= 10; ++j) {
			// Drawing the horizontal row numbers
			if ((i > 0 && i <= 10) && j == 0) {
				print(i * 2 - 1, j + 1, letter);
				letter++;
			}
			// Drawing the vertical row numbers
			if ((j > 0 && j <= 10) && i == 0) {
				print(i, j + 1, j - 1);
			}
		}
	}

	setColor(WHITE);

	// DEBUG MODE ONLY
	// This section will draw the computer's positions
	// Same as the loop above but we draw at different 'j' values
	#ifdef _DEBUG
		letter = 'A';
		print(8, 13, WHITE, "Computer");
		setColor(TEAL);
		for (int i = 0; i <= 10; ++i) {
			for (int j = 0; j <= 10; ++j) {
				if ((i > 0 && i <= 10) && j == 0) {
					print(i * 2 - 1, j + 14, letter);
					letter++;
				}
				if ((j > 0 && j <= 10) && i == 0) {
					print(i, j + 14, j - 1);
				}
			}
		}
	#endif
	setColor(WHITE);
}

/// Deciding the setup mode
int Game::setupSortMode() {
	std::string input = "";
	int sort = 0;
	print(42, 0, "Select your preferred setup method");
	print(42, 1, "1) Automatic\t\t2) Manual");
	print(42, 2, "Type the option and press RETURN");
	print(42, 3, "Choice> ");
	return sort = stringToIntComp(input, "Please input a correct option", eq, 1, 2, 50, 3, 8, 1);
	//return sort;
	// We read a choice from the menu
	//while (true) {
		//gotoxy(50, 2);
		//getline(cin, input);
		//std::stringstream ss(input);
		//readStoI(input, "Please input a correct option", 50, 2);
		//std::stringstream stringToInt(readStoI(input, "Please input a correct option", 50, 2) );
		// Bitwise convertion from string to number
		/*if (stringToInt >> sort) {
			if (sort == 1 || sort == 2) {
				return sort;
			}
			else {
				gotoxy(42, 3);
				cout << "Please input a correct option> ";
			}
		}
		gotoxy(42, 3);
		cout << "Please input a correct option> ";*/
	//}
}

/// Setup of the ships
void Game::computerSort() {

}

void Game::automaticSort() {
	srand((unsigned int)time(NULL));
	int randomSpot = rand() % 5 + 1;
}

void Game::manualSort() {
	// We want to check if either the player and computer have available ships to place
	while (getDeployedShips(0) > 0) {
		
		drawBattleScreen();
		printAvailableShips();

		print(50, 7, "Select a ship to place");
		print(GREEN, ">");
		shipModel = stringToIntComp(strShip, "Input a correct option", outNIR, 0, 5, 74, 7, 24, 1);
		if (playerShips[shipModel - 1] == 1) {
			print(50, 8, "Ship already used");
			//Sleep(750);
		}
		else {
			createShipManual();
		}
	}
}

/// Creating a ship (MANUAL)
void Game::createShipManual() {
	// Vertical screen navigation
	int y = 7;
	// For not using (shipModel - 1)
	int ship_ID = shipModel - 1;
	// Almost ready to create and place our ships
	std::string inputRow;
	std::string inputCol;
	std::string inputDir;
	std::string confirmPlacement;
	char dir;
	int row;
	int col;
	print(50, y + 1, WHITE, "Selected " + availableShipsName[ship_ID] + "(");
	print(GREEN, getShipCode(ship_ID));
	cout << ")";
	print(50, y + 2, "> It has a length of       ");
	cout << getShipSize(ship_ID);
	/// Rows (HORIZONTAL)
	while (true) {
		print(50, y + 3, "> Select row (A - J)");
		print(GREEN, "> ");
		inputRow = readLimitedInput(72, y + 3);
		setColor(WHITE);
		if (inputRow >= "A" && inputRow <= "J") {
			// We convert our string to a character in order to convert it to an int
			char charToInt = inputRow[0];
			// We substract 17 in order to convert it to a number
			row = charToInt - 65;
			for (int i = 42; i < 80; ++i) {
				print(i, y + 4, " ");
			}
			break;
		}
		else {
			print(72, y + 3, " ");
			print(50, y + 4, "Input a correct option");
		}
	}
	/// Columns (VERTICAL)
	while (true) {
		print(50, y + 5, "> Select column (0 - 9)");
		print(GREEN, "> ");
		col = stringToIntComp(inputCol, "Input a correct option", btw, 0, 9, 75, y + 5, 25, 1);
		for (int i = 42; i < 80; ++i) {
			print(i, y + 6, " ");
		}
		break;
	}

	/// Direction
	while (true) {
		print(50, y + 7, "Direction");
		print(50, y + 8, "V(ertical) - H(orizontal)");
		print(GREEN, "> ");
		inputDir = readLimitedInput(77, y + 8);
		setColor(WHITE);
		if (inputDir == "V") {
			dir = 1;
			for (int i = 42; i < 80; ++i) {
				print(i, y + 9, " ");
			}
			break;
		}
		else if (inputDir == "H") {
			dir = -1;
			for (int i = 42; i < 80; ++i) {
				print(i, y + 9, " ");
			}
			break;
		}
		else {
			print(77, y + 8, " ");
			print(50, y + 9, "Input a correct option");
		}
	}

	/// Confirming placement before doing anything else
	while (true) {
		print(50, y + 10, "Confirm placing (Y/N)");
		print(GREEN, "> ");
		confirmPlacement = readLimitedInput(73, y + 10);
		bool tempN = confirmPlacement == "N";
		bool tempY = confirmPlacement == "Y";
		bool tempYN = tempN || tempY;

		if (tempN) {
			return;
		}
		else if (!(tempYN)) {
			print(73, y + 10, " ");
			print(50, y + 11, "Input a correct option");
		}
		else {
			break;
		}
	}
	
	///////////////////// (VERTICAL)
	if (dir == 1) {
		// Vertical and Horizontal collisions
		for (int j = col; j < getShipSize(ship_ID) + col + 1; ++j) {
			if (grid[row][j] == 1) {
				gotoxy(50, y + 11);
				cout << "Position [" << inputRow << ", " << col << "] taken";
				spaceTaken = true;
				break;
			}
		}

		if (spaceTaken == false) {
			// If there aren't any collisions, we set those grid values to 1 (PLACED)
			for (int i = col; i < getShipSize(ship_ID) + col; ++i) {
				grid[row][i] = 1;
			}

			for (int i = col; i < getShipSize(ship_ID) + col; ++i) {
				gotoxy(row * 2 + 1, i + 2);
				cout << getShipCode(ship_ID);
			}

			// Finally, we state that the chosen ship has been taken
			playerShips[ship_ID] = 1;
			availableShips[0]++;
		}
		else {
			spaceTaken = false;
		}
	}
	///////////////////// (HORIZONTAL)
	else {
		// Vertical and Horizontal collisions
		for (int j = row; j < getShipSize(ship_ID) + row + 1; ++j) {
			if (grid[j][col] == 1) {
				gotoxy(50, y + 11);
				cout << "Position [" << inputRow << ", " << col << "] taken";
				spaceTaken = true;
				break;
			}
		}

		if (spaceTaken == false) {
			for (int i = row; i < getShipSize(ship_ID) + row; ++i) {
				grid[i][col] = 1;
			}

			for (int i = row; i < getShipSize(ship_ID) + row; ++i) {
				gotoxy(i * 2 + 1, col + 2);
				cout << getShipCode(ship_ID);
			}

			// Finally, we state that the chosen ship has been taken
			playerShips[ship_ID] = 1;
			availableShips[0]++;
		}
		else {
			spaceTaken = false;
		}
		
	}
}

/// Creating a ship (AUTOMATIC)
void Game::createShipAuto() {
	srand((unsigned int)time(NULL));
}