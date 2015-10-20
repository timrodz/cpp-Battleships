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

//Library includes
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <windows.h>

//Local includes
#include "Game.h"
#include "Screen.h"
//#include "Ship.h"

// Scope renaming
using std::cout;
using std::cin;

Game::Game() {}

Game::~Game() {}

/// Accessor methods
void Game::setFirstRunValue(bool firstRunValue) {
	firstRun = firstRunValue;
}

bool Game::getFirstRunValue() const {
	return firstRun;
}

int Game::getDeployedShips(int i) const {
	return MAX_SHIPS - availableShips[i];
}

void Game::setGrid(int rMax, int cMax) {
	for (int i = 0; i < rMax + 2; ++i) {
		for (int j = 0; j < cMax + 2; ++j) {
			grid[i][j] = 0;
			grid[11][j] = 1;
			grid[i][11] = 1;
			//gotoxy(i + 1, j + 1);
			//cout << grid[i][j];
		}
		
		cout << "\n";
	}
}

void Game::setAvailableShips(int x) {
	playerShips = new int[x];
	computerShips = new int[x];
	for (int i = 0; i < x; ++i) {
		playerShips[i] = 0;
		computerShips[i] = 0;
	}
}

void Game::getAvailableShips() {
	gotoxy(50, 0);
	cout << "Available ships";
	for (int i = 0; i < 5; ++i) {
		if (playerShips[i] == 0) {
			gotoxy(56, i+1);
			cout << i+1 << ") " << availableShipsName[i];
		}
	}
}

// Getting the info of our selected ship
int Game::getShipSize(int shipCode) const {
	if (shipCode == 1) 
		return 5;
	else if (shipCode == 2)
		return 4;
	else if (shipCode == 3)
		return 3;
	else if (shipCode == 4)
		return 3;
	else if (shipCode == 5)
		return 2;
	else
		return 0;
}

char Game::getShipCode(int shipCode) const {
	if (shipCode == 1)
		return '@';
	else if (shipCode == 2)
		return '#';
	else if (shipCode == 3)
		return '&';
	else if (shipCode == 4)
		return '*';
	else if (shipCode == 5)
		return '$';
	else
		return '\0';
}

/// Setup of the ships
void Game::computerSort() {

}

void Game::automaticSort() {
	srand((unsigned int)time(NULL));
	int randomSpot = rand() % 10;
}

void Game::manualSort() {
	// We want to check if either the player and computer have available ships to place
	bool canPlaceShips = getDeployedShips(0) > 0;
	while (canPlaceShips == true) {

		drawBattleScreen();
		getAvailableShips();

		//while (true) {
			gotoxy(50, 7);
			cout << "Select a ship to place> ";
			getline(cin, strShip);
			std::stringstream ss(strShip);
			if (ss >> shipModel) {
				if (shipModel <= 0 || shipModel > 5) {
					gotoxy(50, 8);
					cout << "Input a correct option> ";
				}
				else {
					createShip();
				}
			}
			gotoxy(50, 8);
			cout << "Input a correct option> ";
		}
	//}
}

void Game::createShip() {
	int y = 7;
	// Almost ready to create and place our ships
	std::string inputRow;
	std::string inputCol;
	std::string inputDir;
	char dir;
	int row;
	int col;
	gotoxy(50, y + 1);
	cout << "Selected " << availableShipsName[shipModel - 1];
	gotoxy(50, y + 2);
	cout << "Size: " << getShipSize(shipModel);
	// Checking our rows and columns for flaws (if any)
	// Rows
	while (true) {
		gotoxy(50, y + 3);
		cout << "Select row(A-J)> ";
		getline(cin, inputRow);
		if (inputRow >= "A" && inputRow <= "J") {
			// We convert our string to a character in order to convert it to an int
			char charToInt = inputRow[0];
			// We substract 17 in order to convert it to a number
			row = charToInt - 65;
			break;
		}
		else {
			gotoxy(67, y + 3);
			cout << "             ";
			gotoxy(50, y + 4);
			cout << "Input a correct option> ";
		}
	}
	// Columns
	while (true) {
		gotoxy(50, y + 5);
		cout << "Select column(0-9)> ";
		//cin >> col;
		getline(cin, inputCol);
		std::stringstream ss(inputCol);
		if (ss >> col) {
			if (col >= 0 && col <= 9) {
				break;
			}
			else {
				gotoxy(70, y + 5);
				cout << "          ";
				gotoxy(50, y+6);
				cout << "Input a correct option> ";
			}
		}
		gotoxy(70, y + 5);
		cout << "          ";
		gotoxy(50, y + 6);
		cout << "Input a correct option> ";
		
	}
	
	// Direction
	
	while (true) {
		gotoxy(50, y + 7);
		cout << "Direction";
		gotoxy(50, y + 8);
		cout << "V(ertical) - H(orizontal)> ";
		getline(cin, inputDir);
		//std::stringstream ss(inputDir);
		if (inputDir == "V") {
			dir = 1;
			break;
		}
		else if (inputDir == "H") {
			dir = -1;
			break;
		}
		else {
			gotoxy(50, y + 9);
			cout << "Input a correct option> ";
		}
		gotoxy(50, y + 9);
		cout << "Input a correct option> ";
	}

	// Checking available positions
	// dir = 1 (VERTICAL)
	if (dir == 1) {
		// Vertical and Horizontal collisions
		for (int j = col; j < getShipSize(shipModel) + col + 1; ++j) {
			if (grid[row][j] == 1) {
				gotoxy(50, y + 11);
				cout << "Position [" << inputRow << ", " << col << "] taken";
				spaceTaken = true;
				break;
			}
		}

		if (!spaceTaken) {
			// If there aren't any collisions, we set those grid values to 1 (PLACED)
			for (int i = col; i < getShipSize(shipModel) + col; ++i) {
				grid[row][i] = 1;
			}

			for (int i = col; i < getShipSize(shipModel) + col; ++i) {
				gotoxy(row + 2, i + 2);
				cout << getShipCode(shipModel);
			}

			// Finally, we state that the chosen ship has been taken
			playerShips[shipModel-1] = 1;
			availableShips[0]++;
		}
		else {
			spaceTaken = false;
		}
	}
	// dir = -1 (HORIZONTAL)
	else {
		// Vertical and Horizontal collisions
		for (int j = row; j < getShipSize(shipModel) + row + 1; ++j) {
			if (grid[j][col] == 1) {
				gotoxy(50, y + 11);
				cout << "Position [" << inputRow << ", " << col << "] taken";
				spaceTaken = true;
				break;
			}
		}

		if (!spaceTaken) {
			for (int i = row; i < getShipSize(shipModel) + row; ++i) {
				grid[i][col] = 1;
			}

			for (int i = row; i < getShipSize(shipModel) + row; ++i) {
				gotoxy(i + 2, col + 2);
				cout << getShipCode(shipModel);
			}

			// Finally, we state that the chosen ship has been taken
			playerShips[shipModel-1] = 1;
			availableShips[0]++;
		}
		else {
			spaceTaken = false;
		}
		
	}
}

/// Deciding the setup mode

int Game::setupSortMode() {
	std::string input = "";
	int sort = 0;
	gotoxy(42, 0);
	cout << "Select your preferred setup method";
	gotoxy(42, 1);
	cout << "1) Automatic\t\t2) Manual";
	gotoxy(42, 2);
	cout << "choice> ";
	// We read a choice from the menu
	while (true) {
		gotoxy(50, 2);
		getline(cin, input);
		std::stringstream ss(input);
		// Bitwise convertion from string to number
		if (ss >> sort) {
			if (sort == 1 || sort == 2) {
				return sort;
			}
			else {
				gotoxy(42, 3);
				cout << "Please input a correct option> ";
			}
		}
		gotoxy(42, 3);
		cout << "Please input a correct option> ";
	}
}

void Game::drawBattleScreen() {
	//system("cls");
	clearInput();
	// This will store our letters from A to J
	char letter = 'A';
	gotoxy(2, 0);
	cout << "Player";
	for (int i = 0; i <= 10; ++i) {
		for (int j = 0; j <= 10; ++j) {
			// Drawing the horizontal row numbers
			if ((i > 0 && i <= 10) && j == 0) {
				gotoxy(i+1, j + 1);
				cout << letter;
				letter++;
			}
			// Drawing the vertical row numbers
			if ((j > 0 && j <= 10) && i == 0) {
				gotoxy(i, j + 1);
				cout << j-1;
			}
			
		}
	} // Main loop

	// DEBUG MODE ONLY
	// This section will draw the computer's positions
	// Same as the loop above but we draw at different 'j' values
	#ifdef _DEBUG
	letter = 'A';
	gotoxy(2, 13);
	cout << "Computer";
	for (int i = 0; i <= 10; ++i) {
		for (int j = 0; j <= 10; ++j) {
			if ((i > 0 && i <= 10) && j == 0) {
				gotoxy(i, j + 14);
				cout << letter;
				letter++;
			}
			if ((j > 0 && j <= 10) && i == 0) {
				gotoxy(i, j + 14);
				cout << j - 1;
			}

		}
	}
	#endif
}

void Game::clearInput() {
	for (int i = 42; i < 80; ++i) {
		for (int j = 0; j <= 24; ++j) {
			gotoxy(i, j);
			cout << " ";
		}
	}
}

void Game::gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	COORD dwCursorPosition;
	lpCursor.bVisible = false;
	lpCursor.dwSize = 1;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	//SetConsoleCursorInfo(consoleHandle, &lpCursor);
	SetConsoleCursorPosition(consoleHandle, dwCursorPosition);
}