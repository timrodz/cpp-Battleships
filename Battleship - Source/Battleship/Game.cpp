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

// This condition will make certain code only run if _DEBUG is defined (when in Debug build)
#ifdef _DEBUG
#define DEBUG_IF(cond) if(cond)
#else
#define DEBUG_IF(cond) if(false)
#endif

// Library includes
#include <iostream>
#include <string>
//#include <sstream>
#include <ctime>
#include <windows.h>

// Local includes
#include "Game.h"
#include "Screen.h"

// Scope renaming
using std::string;
using std::cout;
using std::cin;

// Constant static variables
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
	// Setting the grid
	setGrid();
	// Setting the available ships
	setAvailableShips();
}

Game::Game(const Game& game) {

}

Game::~Game() {
	delete[] currentPlayerShip;
	delete[] currentComputerShip;
	currentPlayerShip = 0;
	currentComputerShip = 0;
}

/// Accessor methods
void Game::setFirstRunValue(bool firstRunValue) {
	firstRun = firstRunValue;
}

bool Game::getFirstRunValue() const {
	return firstRun;
}

int Game::getSortMode() const {
	return sort;
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
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; ++j) {
			grid[i][j] = 0;
			grid[11][j] = 1;
			grid[i][11] = 1;
		}
	}
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 10; ++j) {
			print(i + 1, j + 2, DARKTEAL, "~");
			DEBUG_IF(1) {
				print(i + 1, j + 15, DARKTEAL, "~");
			}
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
			print(56, i + 1, std::to_string(i + 1) + ") " + SHIP_NAME[i] + "(");
			print(GREEN, getShipCode(i));
			cout << ")";
		}
		else {
			print(56, i + 1, std::to_string(i + 1) + ") ");
			print(RED, "ALEADY PLACED");
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

/// Drawing screens
void Game::drawMenuScreen() {



}

void Game::drawSetupScreen() {
	clearInput(44);
	// This will store our letters from A to J
	char letter = 'A';
	print(7, 0, YELLOW, "Player");
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
	DEBUG_IF(1) {
		letter = 'A';
		print(6, 13, YELLOW, "Computer");
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
	}
	setColor(WHITE);
}

void Game::drawGameScreen() {
	clearInput(44);
	char letter = 'A';
	print(7 + 22, 0, YELLOW, "Strategy");
	setColor(TEAL);
	for (int i = 0; i <= 20; ++i) {
		for (int j = 0; j <= 10; ++j) {
			//if ((j == 0 || j == 10)) {
			if (j == 0 || j == 10) {
				print(i + 22, j + 1, "#");
			} if (i == 0 || i == 10 || i == 20) {
				print(i + 22, j + 1, "#");
			}
		}
	}
	print(25, 2, YELLOW, "Moves");
	print(36, 2, YELLOW, "Hits");
}

void Game::drawGameOverScreen() {



}

void Game::drawQuitScreen() {
	clearInput(0);
	int x = 5;
	int y = 2;
	print(x, ++y, GREEN, ".___________. __    __       ___      .__   __.  __  ___      _______.");
	print(x, ++y, GREEN, "|           ||  |  |  |     /   \\     |  \\ |  | |  |/  /     /       |");
	print(x, ++y, GREEN, "`---|  |----`|  |__|  |    /  ^  \\    |   \\|  | |  '  /     |   (----`");
	print(x, ++y, GREEN, "    |  |     |   __   |   /  /_\\  \\   |  . `  | |    <       \\   \\    ");
	print(x, ++y, GREEN, "    |  |     |  |  |  |  /  _____  \\  |  |\\   | |  .  \\  .----)   |   ");
	print(x, ++y, GREEN, "    |__|     |__|  |__| /__/     \\__\\ |__| \\__| |__|\\__\\ |_______/    ");
	x = 25;
	++y;
	print(x, ++y, GREEN, " _______   ______   .______      ");
	print(x, ++y, GREEN, "|   ____| /  __  \\  |   _  \\     ");
	print(x, ++y, GREEN, "|  |__   |  |  |  | |  |_)  |    ");
	print(x, ++y, GREEN, "|   __|  |  |  |  | |      /     ");
	print(x, ++y, GREEN, "|  |     |  `--'  | |  |\\  \\----.");
	print(x, ++y, GREEN, "|__|      \\______/  | _| `._____|");
	x = 5;
	++y;
	print(x, ++y, GREEN, ".______    __          ___   ____    ____  __  .__   __.   _______  __  ");
	print(x, ++y, GREEN, "|   _  \\  |  |        /   \\  \\   \\  /   / |  | |  \\ |  |  /  _____||  | ");
	print(x, ++y, GREEN, "|  |_)  | |  |       /  ^  \\  \\   \\/   /  |  | |   \\|  | |  |  __  |  | ");
	print(x, ++y, GREEN, "|   ___/  |  |      /  /_\\  \\  \\_    _/   |  | |  . `  | |  | |_ | |  | ");
	print(x, ++y, GREEN, "|  |      |  `----./  _____  \\   |  |     |  | |  |\\   | |  |__| | |__| ");
	print(x, ++y, GREEN, "| _|      |_______/__/     \\__\\  |__|     |__| |__| \\__|  \\______| (__) ");
	x = 25;
	++y;
	gotoxy(x, ++y, true);
	system("pause");
}



/**************************************/
/*                SETUP               */
/**************************************/

/// Deciding the setup mode
int Game::setupSortMode() {
	print(44, 0, "Select your preferred setup method");
	print(44, 1, "1) Automatic\t2) Manual");
	print(44, 2, "Type the option and press RETURN");
	print(44, 3, "Choice> ");
	sort = stringToInt(input, "Please input a correct option", eq, 1, 2, 52, 3, 8, 1);
	if (sort != -1) {
		return sort;
	}
	else {
		return -1;
	}
}

void Game::sortAuto() {
	int i = 0;
	drawSetupScreen();
	print(44, 0, GREEN, "> Setting your ships................");
	while (getDeployedShips(0) > 0) {
		createShipAuto(0);
	}
	print(76, 0, YELLOW, "DONE");

	print(44, 1, GREEN, "> Setting opponents's ships.........");
	while (getDeployedShips(1) > 0) {
		createShipAuto(1);
	}
	print(76, 1, YELLOW, "DONE");
	print(44, 3, GREEN, "> Setup finished!");
	print(44, 5, GREEN, "> Setting up the match..............");
	Sleep(3000);
}

void Game::sortManual() {
	// We want to check if either the player and computer have available ships to place
	while (getDeployedShips(0) > 0) {

		drawSetupScreen();
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
	clearInput(44);
	print(44, 0, GREEN, "> Please wait.......................");
	print(44, 1, GREEN, "> Setting opponents's ships.........");
	while (getDeployedShips(1) > 0) {
		createShipAuto(1);
	}
	print(76, 1, YELLOW, "DONE");
	print(44, 3, GREEN, "> Setup finished!");
	print(44, 5, GREEN, "> Setting up the match..............");
	setCancelSort("NOTCANCELED");
	Sleep(3000);
	
}

/// Creating a ship (AUTOMATIC)
void Game::createShipAuto(int player) {

	srand((unsigned int)time(NULL));
	
	int tempShip = rand() % 5;
	int tempRow = rand() % 10;
	int tempCol = rand() % 10;
	int tempDir = rand() % 2;

	// Checking whether or not the ship is available for use
	while (true) {
		if (player == 0 || player == 1) {
			if (player == 0) {
				if (currentPlayerShip[tempShip] == 1) {
					tempShip = rand() % 5;
				}
				else
					break;
			}
			else if (player == 1) {
				if (currentComputerShip[tempShip] == 1) {
					tempShip = rand() % 5;
				}
				else
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
	// Since arrays are counted starting from 0
	int ship_ID = shipModel - 1;
	
	string inputCol, inputDir, confirmPlacement;
	int row, col;
	char dir;

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
			char charToInt = inputRow[0];
			row = charToInt - 65;

			for (int i = 44; i < 80; ++i) 
				print(i, y + 4, " ");
			
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
		for (int i = 44; i < 80; ++i)
			print(i, y + 6, " ");
		
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
		if (inputDir == "V" || inputDir == "H") {

			if (inputDir == "V")
				dir = 1;
			else if (inputDir == "H")
				dir = -1;
			
			for (int i = 44; i < 80; ++i) 
				print(i, y + 9, " ");
			
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

		if (confirmPlacement == "N") {
			return;
		}
		else if (!(confirmPlacement == "N" || confirmPlacement == "Y")) {
			print(73, y + 10, " ");
			print(50, y + 11, "Input a correct option");
		}
		else {
			break;
		}
	}

	placeShip(dir, row, col, ship_ID, 0);
}

/// Placing the ships for the player and the AI
void Game::placeShip(int dir, int row, int col, int ship_ID, int player) {

	// For the loop iterator
	int shipArray;
	int shipArrayOriginalValue;
	int currentGridPosition;
	int nextGridPosition;

	if (dir == 1) {
		shipArray = col;
		shipArrayOriginalValue = col;
	}
	else {
		shipArray = row;
		shipArrayOriginalValue = row;
	}
	for (int tempPosition = shipArray; tempPosition < getShipSize(ship_ID) + shipArray; ++tempPosition) {

		if (dir == 1) {
			currentGridPosition = grid[row][tempPosition];
			nextGridPosition = grid[row][tempPosition + 1];
		}
		else {
			currentGridPosition = grid[tempPosition][col];
			nextGridPosition = grid[tempPosition + 1][col];
		}

		// Substract 2 in order to show a correct coordinate
		if (tempPosition >= 9 && nextGridPosition == 1) {
			if (getSortMode() == 2 && player == 0) {
				tempPosition -= 2;
				print(50, 19, RED, "##### OUT OF BOUNDS #####");
				Sleep(1250);
			}
			return;
		}

		if (currentGridPosition == 1) {
			spaceTaken = true;
			if (getSortMode() == 2 && player == 0) {
				print(50, 19, RED, "Position [" + inputRow + ", " + std::to_string(tempPosition) + "] taken");
				Sleep(1250);
			}
			break;
		}
	}

	if (spaceTaken == false) {
		for (int tempPosition = shipArray; tempPosition < getShipSize(ship_ID) + shipArray; ++tempPosition) {
			if (dir == 1) {
				grid[row][tempPosition] = 1;
				if (player == 0) {
					print(row * 2 + 1, tempPosition + 2, GREEN, getShipCode(ship_ID));
				}
				else {
					DEBUG_IF(1) {
						print(row * 2 + 1, tempPosition + 15, GREEN, getShipCode(ship_ID));
					}
				}

			}
			else {
				grid[tempPosition][col] = 1;
				if (player == 0) {
					print(tempPosition * 2 + 1, col + 2, GREEN, getShipCode(ship_ID));
				}
				else {
					DEBUG_IF(1) {
						print(tempPosition * 2 + 1, col + 15, GREEN, getShipCode(ship_ID));
					}
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