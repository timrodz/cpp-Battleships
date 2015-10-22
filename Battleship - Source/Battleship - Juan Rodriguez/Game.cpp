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

/// Constructor
Game::Game() {
	/// For determining which space has been taken in order to place ships
	spaceTaken = false;
	/// Player ships
	currentShipsPlaced[0] = 0;
	/// Computer ships
	currentShipsPlaced[1] = 0;
}

Game::Game(const Game& game) {

}

/// Destructor
Game::~Game() {
	delete[] currentPlayerShip;
	delete[] currentComputerShip;
	currentPlayerShip = 0;
	currentComputerShip = 0;
}

/// Game start ///

void Game::setCollisionGrid() {
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; ++j) {
			grid[i][j] = 0;
			grid[11][j] = 1;
			grid[i][11] = 1;
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

void Game::setState(string sortValue) {
	cancelSort = sortValue;
}

string Game::getState() const {
	return cancelSort;
}

int Game::getPlacedShips(int i) const {
	return MAX_SHIPS - currentShipsPlaced[i];
}

bool Game::canPlaceShips(int i) const {
	return (getPlacedShips(i) > 0);
}

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

/**************************************/
/*                                    */
/*                MENU                */
/*                                    */
/**************************************/

void Game::drawMenuScreen() {
	clearText(0);
	int x = 17;
	int y = 0;
	print(x, y, GREEN, "___  ____ ___ ___ _    ____ ____ _  _ _ ___ ");
	print(x, ++y, GREEN, "|__] |__|  |   |  |    |___ [__  |__| | |__]");
	print(x, ++y, GREEN, "|__] |  |  |   |  |___ |___ ___] |  | | |   ");
	y = 10;
	print(x, y, "1) Play          2) Credits          3) Exit");
	print(x, ++y, "Type your option and press ");
	print(GREEN, "RETURN");
	print(x, ++y, "Option");
	print(GREEN, "> ");
	y = 16;
	DEBUG_IF(1) {
		print(0, 24, "Debug mode (Can see computer's movements)");
	}
}

int Game::setMenu() {
	string inputOption;
	menuOption = stringToInt(inputOption, "Please provide a correct choice", btw, 1, 3, 25, 12, 8, 1);;
	return menuOption;
}

/**************************************/
/*                                    */
/*                SETUP               */
/*                                    */
/**************************************/

/// Draw setup screen
void Game::drawSetupScreen() {
	clearText(0);
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

	// Drawing the water
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 10; ++j) {
			print(i + 1, j + 2, DARKTEAL, "~");
			DEBUG_IF(1) {
				print(i + 1, j + 15, DARKTEAL, "~");
			}
		}
	}
}

/// Deciding the setup mode
int Game::setSetupMode() {

	// Printing instructions
	int x = 44;
	int y = 0;

	print(x, y, GREEN, "INSTRUCTIONS:");
	print(x, ++y, "You must set up 5 ships. They have");
	print(x, ++y, "varying lenghts, so plan properly.");
	print(x, ++y, "You must choose your setup method.");
	print(x, y += 2, GREEN, "FOR MANUAL SETUP:");
	print(x, ++y, "You'll be asked for a position to");
	print(x, ++y, "place your ship as follows:");
	print(x, ++y, "Rows      (A - J)");
	print(x, ++y, "Columns   (0 - 9)");
	print(x, ++y, "Direction (Vertical - Horizontal)");
	print(x, y += 2, GREEN, "IN GAME:");
	print(x, ++y, "Destroy your opponent's ships.");
	print(x, ++y, "Guess a position e.g. A0, B7, D4");
	print(x, ++y, "If there's a ship, it will hit it");
	print(x, ++y, "marking the ");
	print(RED, "spot ");
	print(WHITE, "where it was hit.");
	print(x, y += 2, "The opponent can hit you as well.");
	print(x, y += 2, GREEN, "SELECT SETUP METHOD (ESC to exit)");
	print(x, ++y, GREEN, "1)");
	print(WHITE, " Automatic - ");
	print(GREEN, "2)");
	print(WHITE, " Manual");
	print(x, ++y, "Type your option and press ");
	print(GREEN, "RETURN");
	print(x, ++y, "Option");
	print(GREEN, "> ");
	x = 52;

	// Reading our sort value (1: auto | 2: manual)
	sortValue = stringToInt(inputSort, "Please provide a correct option", eq, 1, 2, x, y, 8, 1);
	if (sortValue != -1) {
		return sortValue;
	}
	else {
		setState("NOTCANCELED");
		return 0;
	}
}

/// Get sort mode
int Game::getSetupMode() const {
	return sortValue;
}

/// Print available ships
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

/// Setting rows and columns
void Game::getCoordinates(string& inputRow, string& inputCol, int& row, int& col, int x, int y) {
	//string inputRow, inputCol;
	/// Rows (HORIZONTAL)
	while (true) {
		print(x, y, "> Select row (A - J)");
		print(GREEN, "> ");
		inputRow = readLimitedInput(x + 22, y);
		if (inputRow == "CANCEL") {
			setState("CANCEL");
			return;
		}
		setColor(WHITE);
		string tempString(inputRow);
		if (inputRow >= "A" && inputRow <= "J") {
			char charToInt = tempString.at(0);
			row = charToInt - 65;

			for (int i = 44; i < 80; ++i)
				print(i, y + 1, " ");

			break;
		}
		else {
			print(72, y, " ");
			print(50, y + 1, "Provide a correct option");
		}
	}
	/// Columns (VERTICAL)
	while (true) {
		print(x, y += 2, "> Select column (0 - 9)");
		print(GREEN, "> ");
		col = stringToInt(inputCol, "Provide a correct option", btw, 0, 9, x + 25, y, 25, 1);
		if (col == -1) {
			setState("CANCEL");
			return;
		}
		for (int i = 44; i < 80; ++i)
			print(i, y + 1, " ");

		break;
	}
}

/// Automatic sort
void Game::sortAuto() {
	clearText(44);
	print(44, 0, GREEN, "> Setting your ships................");
	while (getPlacedShips(0) > 0) {
		createShipAuto(0);
	}
	print(76, 0, YELLOW, "DONE");

	print(44, 1, GREEN, "> Setting opponents's ships.........");
	while (getPlacedShips(1) > 0) {
		createShipAuto(1);
	}
	print(76, 1, YELLOW, "DONE");
	print(44, 3, GREEN, "> Setup finished!");
	print(44, 5, GREEN, "> Setting up the match..............");
	Sleep(3000);
}

/// Manual sort
void Game::sortManual() {
	// We want to check if either the player and computer have available ships to place
	while (getPlacedShips(0) > 0) {

		clearText(44);
		printAvailableShips();

		while (true) {
			print(50, 7, "Select a ship to place");
			print(GREEN, ">");
			shipModel = stringToInt(inputShip, "Provide a correct option", outNIR, 0, 5, 74, 7, 24, 1);
			if (shipModel == -1) {
				setState("CANCEL");
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
	clearText(44);
	print(44, 0, GREEN, "> Please wait.......................");
	print(44, 1, GREEN, "> Setting opponents's ships.........");
	while (getPlacedShips(1) > 0) {
		createShipAuto(1);
	}
	print(76, 1, YELLOW, "DONE");
	print(44, 3, GREEN, "> Setup finished!");
	print(44, 5, GREEN, "> Setting up the match..............");
	setState("NOTCANCELED");
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
	int x = 50;
	int y = 7;
	// Since arrays are counted starting from 0
	int SHIP_ID = shipModel - 1;
	
	string inputCol, inputDir, confirmPlacement;
	int row, col;
	char dir;

	print(x, ++y, WHITE, "Selected ");
	print(GREEN, SHIP_NAME[SHIP_ID]); 
	cout << "(";
	print(GREEN, getShipCode(SHIP_ID));
	cout << ")";
	print(x, ++y, "It has a length of.........");
	setColor(GREEN);
	cout << getShipSize(SHIP_ID);
	setColor(WHITE);

	// Gettings rows and columns
	getCoordinates(inputRow, inputCol, row, col, x, y += 2);
	y += 4;

	/// Direction
	while (true) {
		print(x, y, "Direction");
		print(50, y + 1, "V(ertical) - H(orizontal)");
		print(GREEN, "> ");
		inputDir = readLimitedInput(x + 27, y + 1);
		if (inputDir == "CANCEL") {
			setState("CANCEL");
			return;
		}
		setColor(WHITE);
		if (inputDir == "V" || inputDir == "H") {

			if (inputDir == "V")
				dir = 1;
			else if (inputDir == "H")
				dir = -1;
			
			for (int i = 44; i < 80; ++i) 
				print(i, y + 2, " ");
			
			break;
		}
		else {
			print(77, y + 1, " ");
			print(50, y + 2, "Provide a correct option");
		}
	}

	y += 3;

	/// Confirming placement before doing anything else
	while (true) {
		print(50, y, "Confirm placing (Y/N)");
		print(GREEN, "> ");
		confirmPlacement = readLimitedInput(x + 23, y);

		if (confirmPlacement == "N") {
			return;
		}
		else if (!(confirmPlacement == "N" || confirmPlacement == "Y")) {
			print(73, y, " ");
			print(50, y + 1, "Provide a correct option");
		}
		else {
			break;
		}
	}
	placeShip(dir, row, col, SHIP_ID, 0);
}

/// Placing the ships for the player and the AI
/// It relies on the value of 'spaceTaken' to operate
/// Directions -> 1: Vertical - 2: Horizontal
void Game::placeShip(int dir, int row, int col, int SHIP_ID, int player) {

	// For our loops
	int position;
	int currentGridPos;
	int nextGridPos;

	if (dir == 1) {
		position = col;
	}
	else {
		position = row;
	}
	
	// Collision checking (includes out of bounds)
	for (int temp = position; temp < getShipSize(SHIP_ID) + position; ++temp) {

		if (dir == 1) {
			currentGridPos = grid[row][temp];
			nextGridPos = grid[row][temp + 1];
		}
		else {
			currentGridPos = grid[temp][col];
			nextGridPos = grid[temp + 1][col];
		}

		if (temp >= 9 && nextGridPos == 1) {
			if (getSetupMode() == 2 && player == 0) {
				temp -= 2;
				print(50, 20, RED, "####  ");
				print(YELLOW, "OUT OF BOUNDS");
				print(RED, "  ####");
				print(50, 21, RED, "####    ");
				print(YELLOW, "TRY AGAIN");
				print(RED, "    ####");
				Sleep(1500);
			}
			return;
		}

		if (currentGridPos == 1) {
			spaceTaken = true;
			if (getSetupMode() == 2 && player == 0) {
				print(50, 20, RED, "##  "); 
				print(YELLOW, "Position " + inputRow + std::to_string(temp) + " occupied");
				print(RED, "  ##");
				print(50, 21, RED, "##       ");
				print(YELLOW, "TRY AGAIN");
				print(RED, "       ##");
				Sleep(1500);
			}
			break;
		}
	}

	// Proceeding to the actual placing
	if (spaceTaken == false) {
		for (int tempPosition = position; tempPosition < getShipSize(SHIP_ID) + position; ++tempPosition) {
			if (dir == 1) {
				grid[row][tempPosition] = 1;
				if (player == 0) {
					print(row * 2 + 1, tempPosition + 2, GREEN, getShipCode(SHIP_ID));
				}
				else {
					DEBUG_IF(1) {
						print(row * 2 + 1, tempPosition + 15, GREEN, getShipCode(SHIP_ID));
					}
				}

			}
			else {
				grid[tempPosition][col] = 1;
				if (player == 0) {
					print(tempPosition * 2 + 1, col + 2, GREEN, getShipCode(SHIP_ID));
				}
				else {
					DEBUG_IF(1) {
						print(tempPosition * 2 + 1, col + 15, GREEN, getShipCode(SHIP_ID));
					}
				}

			}
		}
		// Making the ship unavailable now that it has been placed
		// 0 = player, 1 = AI
		if (player == 0) {
			currentPlayerShip[SHIP_ID] = 1;
		}
		else if (player == 1) {
			currentComputerShip[SHIP_ID] = 1;
		}
		currentShipsPlaced[player]++;
	}
	else {
		spaceTaken = false;
	}
}

/**************************************/
/*                                    */
/*                GAME                */
/*                                    */
/**************************************/

void Game::drawGameScreen() {
	clearText(44);
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
	print(25, 2, YELLOW, "Miss");
	print(36, 2, YELLOW, "Hits");
}

void Game::update() {
	string inputCol;
	int x = 50;
	int y = 0;
	int row, col;
	print(x,   y, GREEN, "YOUR TURN");
	print(x, ++y, GREEN, "TRY TO HIT YOUR OPPONENT");
	//print(x, ++y, "");
	getCoordinates(inputRow, inputCol, row, col, x, ++y);
	print(x, ++y, row);
	print(x, ++y, col);
}

/**************************************/
/*                                    */
/*             GAME OVER              */
/*                                    */
/**************************************/

void Game::drawGameOverScreen() {
	clearText(0);
	int x = 17;
	int y = 0;
	print(x, y, GREEN, "___  ____ ___ ___ _    ____ ____ _  _ _ ___ ");
	print(x, ++y, GREEN, "|__] |__|  |   |  |    |___ [__  |__| | |__]");
	print(x, ++y, GREEN, "|__] |  |  |   |  |___ |___ ___] |  | | |   ");
	y = 10;
	print(x, y, "PLAY AGAIN?");
	print(x, ++y, "Y(es)/N(no)");
	print(x, ++y, "Type your option and press ");
	print(GREEN, "RETURN");
	print(x, ++y, "Option");
	print(GREEN, "> ");
}

string Game::setGameOver() {
	string inputOption;
	while (true) {
		inputOption = readLimitedInput(25, 13);
		if (inputOption != "Y" && inputOption != "N") {
			print(25, 13, " ");
			print(17, 14, "Please provide a correct option");
		}
		else {
			for (int i = 44; i < 80; ++i) {
				print(i, 13, " ");
			}
			break;
		}
	}
	return inputOption;
}

/**************************************/
/*                                    */
/*           QUIT / CREDITS           */
/*                                    */
/**************************************/

void Game::drawQuitScreen() {
	clearText(0);
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

void Game::drawCreditsScreen() {
	clearText(0);
	int x = 25;
	int y = 3;

	for (int i = 0; i < 80; ++i) {
		for (int j = 0; j < 24; ++j) {
			if (j == 0 || j == 23) {
				print(i, j, GREEN, "#");
			} if (i == 0 || i == 79) {
				print(i, j, GREEN, "#");
			}
		}
	}

	print(x, y += 2, "Media Design School");
	print(x, y += 2, "Auckland");
	print(x, y += 2, "New Zealand");
	y += 2;
	print(x, y += 2, "Lecturer: Bindu Ojha");
	print(x, y += 2, "Student: Juan Rodriguez");
	y += 2;
	gotoxy(x, y += 2, true);
	system("pause");
}