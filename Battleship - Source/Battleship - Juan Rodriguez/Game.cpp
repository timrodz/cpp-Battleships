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
using std::string;
using std::cout;
using std::cin;

// Static variables
const int Game::MAX_SHIPS = 5;
const string Game::SHIP_NAME[5] = {
	"Aircraft Carrier ",
	"Battleship       ",
	"Destroyer        ",
	"Submarine        ",
	"Patrol Boat      "
};

Game::Game() {
	// For determining which space has been taken in order to place ships
	spaceTaken = false;
	// Player ships
	currentShipsPlaced[0] = 0;
	// Computer ships
	currentShipsPlaced[1] = 0;
}

Game::~Game() {}

/// Accessor methods
void Game::setFirstRunValue(bool firstRunValue) {
	firstRun = firstRunValue;
}

bool Game::getFirstRunValue() const {
	return firstRun;
}

void Game::setCancelSort(string sort) {
	cancelSort = sort;
}

string Game::getCancelSort() const {
	return cancelSort;
}

bool Game::canPlaceShips(int i) const {
	return (getDeployedShips(i) > 0);
}

int Game::getDeployedShips(int i) const {
	return MAX_SHIPS - currentShipsPlaced[i];
}

void Game::setGrid() {
	for (int i = 0; i < 11; ++i) {
		for (int j = 0; j < 11; ++j) {
			grid[i][j] = 0;
			grid[10][j] = 1;
			grid[i][10] = 1;
		}
		cout << "\n";
	}
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 10; ++j) {
			print(i + 1, j + 2, DARKTEAL, "~");
		}
	}
}

void Game::setAvailableShips() {
	currentPlayerShip = new int[5];
	currentComputerShip = new int[5];
	for (int i = 0; i < 5; ++i) {
		currentPlayerShip[i] = 0;
		currentComputerShip[i] = 0;
	}
}

// Prints the current ships in the right corner of the screen (Manual sort only)
void Game::printAvailableShips() {
	print(50, 0, "Available ships (ESC to exit)");
	for (int i = 0; i < 5; ++i) {
		if (currentPlayerShip[i] == 0) {
			print(56, i + 1, std::to_string(i+1) + ") " + SHIP_NAME[i] + "(");
			print(GREEN, getShipCode(i));
			cout << ")";
		}
		else {
			gotoxy(56, i + 1);
			cout << i + 1<< ") ";
			setColor(RED);
			cout << "ALREADY PLACED";
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
	print(42, 0, "Select your preferred setup method");
	print(42, 1, "1) Automatic\t\t2) Manual");
	print(42, 2, "Type the option and press RETURN");
	print(42, 3, "Choice> ");
	sort = stringToInt(input, "Please input a correct option", eq, 1, 2, 50, 3, 8, 1);
	if (sort != -1) {
		return sort;
	}
	else {
		return -1;
	}
}

int Game::getSortMode() const {
	return sort;
}

void Game::sortAuto() {
	drawBattleScreen();
	while (getDeployedShips(0) > 0) {
		createShipAuto(0);
	}
	while (getDeployedShips(1) > 0) {
		createShipAuto(1);
	}
}

void Game::sortManual() {
	// We want to check if either the player and computer have available ships to place
	while (getDeployedShips(0) > 0) {
		
		drawBattleScreen();
		printAvailableShips();

		while (true) {
			print(50, 7, "Select a ship to place");
			print(GREEN, ">");
			shipModel = stringToInt(strShip, "Input a correct option", outNIR, 0, 5, 74, 7, 24, 1);
			if (shipModel == -1) {
				setCancelSort("CANCEL");
				return;
			}
			if (currentPlayerShip[shipModel - 1] == 1) {
				print(74, 7, " ");
				print(50, 8, "Ship already used");
			}
			else {
				break;
			}
		}
		createShipManual();
	}

}

/// Creating a ship (AUTOMATIC)
void Game::createShipAuto(int player) {
	srand((unsigned int)time(NULL));
	int tempShip = rand() % 5;
	int tempRow  = rand() % 10;
	int tempCol  = rand() % 10;
	int tempDir  = rand() % 2;

	// Checking whether or not the ship is available for use
	while (true) {
		if (player == 0) {
			if (currentPlayerShip[tempShip] == 1) {
				tempShip = rand() % 5;
			}
			else {
				break;
			}
		}
		else if (player == 1) {
			if (currentComputerShip[tempShip] == 1) {
				tempShip = rand() % 5;
			}
			else {
				break;
			}
		}
	}
	placeShip(tempDir, tempRow, tempCol, tempShip, player);
}

/// Creating a ship (MANUAL)
void Game::createShipManual() {
	// Vertical screen navigation
	int y = 7;
	// For not using (shipModel - 1)
	int ship_ID = shipModel - 1;
	// Almost ready to create and place our ships
	//string inputRow;
	string inputCol;
	string inputDir;
	string confirmPlacement;
	char dir;
	int row;
	int col;
	print(50, y + 1, WHITE, "Selected " + SHIP_NAME[ship_ID] + "(");
	print(GREEN, getShipCode(ship_ID));
	cout << ")";
	print(50, y + 2, "> It has a length of       ");
	cout << getShipSize(ship_ID);
	/// Rows (HORIZONTAL)
	while (true) {
		print(50, y + 3, "> Select row (A - J)");
		print(GREEN, "> ");
		inputRow = readLimitedInput(72, y + 3);
		if (inputRow == "CANCEL") {
			setCancelSort("CANCEL");
			return;
		}
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
		col = stringToInt(inputCol, "Input a correct option", btw, 0, 9, 75, y + 5, 25, 1);
		if (col == -1) {
			setCancelSort("CANCEL");
			return;
		}
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
		if (inputDir == "CANCEL") {
			setCancelSort("CANCEL");
			return;
		}
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
	
	placeShip(dir, row, col, ship_ID, 0);
}

void Game::placeShip(int dir, int row, int col, int ship_ID, int player) {

	// For the loop iterator
	int shipArray;
	int shipArrayOriginalValue;
	int currentGridPosition;

	if (dir == 1) {
		shipArray = col;
		shipArrayOriginalValue = col;
	}
	else {
		shipArray = row;
		shipArrayOriginalValue = row;
	}
	for (int tempPosition = shipArray; tempPosition < getShipSize(ship_ID) + shipArray + 1; ++tempPosition) {

		if (dir == 1) {
			currentGridPosition = grid[row][tempPosition];
		}
		else {
			currentGridPosition = grid[tempPosition][col];
		}

		if (currentGridPosition == 1) {
			spaceTaken = true;
			if (getSortMode() == 2) {
				print(50, 19, "Position [" + inputRow + ", " + std::to_string(tempPosition) + "] taken");
				Sleep(1000);
			}
			break;
		}
	}

	if (spaceTaken == false) {
		for (int tempPosition = shipArray; tempPosition < getShipSize(ship_ID) + shipArray + 1; ++tempPosition) {
			if (dir == 1) {
				grid[row][tempPosition] = 1;
				if (player == 0) {
					print(row * 2 + 1, tempPosition + 2, GREEN, getShipCode(ship_ID));
				}
				else {
					print(row * 2 + 1, tempPosition + 15, GREEN, getShipCode(ship_ID));
				}
				
			}
			else {
				grid[tempPosition][col] = 1;
				if (player == 0) {
					print(tempPosition * 2 + 1, col + 2, GREEN, getShipCode(ship_ID));
				}
				else {
					print(tempPosition * 2 + 1, col + 15, GREEN, getShipCode(ship_ID));
				}
				
			}		
		}
		// Making the ship unavailable now that it has been placed
		// 0 = player, 1 = AI
		if (player == 0) {
			currentPlayerShip[ship_ID] = 1;
		}
		else if (player == 1) {
			currentComputerShip[ship_ID] = 1;
		}
		currentShipsPlaced[player]++;
	}
	else {
		spaceTaken = false;
	}
}