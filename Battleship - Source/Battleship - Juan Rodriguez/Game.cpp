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

// This condition will make certain code only run if _DEBUG is defined (Debug build)
#ifdef _DEBUG
#define DEBUG_IF(cond) if(cond)
#else
#define DEBUG_IF(cond) if(false)
#endif

// Library includes
#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>

// This include
#include "Game.h"

// Wrapping std::functions
using std::string;
using std::cout;
using std::cin;

// Initializing static variables
const int    Game::MAX_SHIPS = 5;
const string Game::SHIP_NAME[5] = {
	"Aircraft Carrier ",
	"Battleship       ",
	"Destroyer        ",
	"Submarine        ",
	"Patrol Boat      "
};

// Constructor ///
Game::Game() {
	/// Seeding the random generator
	srand((unsigned int)time(NULL));
	/// Allocating memory for our currentShips
	currentPlayerShip = new int[5];
	currentComputerShip = new int[5];
	/// For determining which space has been taken in order to place ships
	spaceTaken = false;
	/// Hit/miss counters
	// Player
	hitCounter[0] = 0;
	// Computer
	hitCounter[1] = 0;
}

// Destructor ///
Game::~Game() {
	delete[] currentPlayerShip;
	delete[] currentComputerShip;
	currentPlayerShip = 0;
	currentComputerShip = 0;
}

// Game start ///
void Game::setCollisionGrid() {
	// Player
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; ++j) {
			playerGrid[i][j] = 0;
			playerGrid[11][j] = 1;
			playerGrid[i][11] = 1;
		}
	}
	// Computer
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; ++j) {
			computerGrid[i][j] = 0;
			computerGrid[11][j] = 1;
			computerGrid[i][11] = 1;
		}
	}
}

// Resets the ships
void Game::setAvailableShips() {
	// Resetting current ships
	for (int i = 0; i < 5; ++i) {
		currentPlayerShip[i] = 0;
		currentComputerShip[i] = 0;
	}
	// Player ships and hit counter
	currentShipsPlaced[0] = 0;
	hitCounter[0] = 0;
	// Computer ships and hit counter
	currentShipsPlaced[1] = 0;
	hitCounter[1] = 0;
}

void Game::setState(string setupMode) {
	cancelSort = setupMode;
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

// Drawing the menu screen
void Game::drawMenuScreen() {

	drawScreenBorders();

	int x = 17;
	int y = 5;
	// Text
	print(x,   y, TEAL, "___  ____ ___ ___ _    ____ ____ _  _ _ ___ ");
	print(x, ++y, TEAL, "|__] |__|  |   |  |    |___ [__  |__| | |__]");
	print(x, ++y, TEAL, "|__] |  |  |   |  |___ |___ ___] |  | | |   ");
	y += 8;
	print(x, y, PINK, "1) ");
	print(WHITE, "Play          "); 
	print(PINK,  "2) ");
	print(WHITE, "Credits          ");
	print(PINK,  "3) ");
	print(WHITE, "Exit");
	print(x, ++y, "Type your option and press ");
	print(GREEN, "RETURN");
	print(x, ++y, "Option");
	print(GREEN, "> ");
	DEBUG_IF(1) {
		print(3, 23, DARKPINK, "Debug mode");
	}
}

// Reading the option of the menu to navigate through
int Game::setMenu() {
	string inputOption;
	menuOption = stringToInt(inputOption, "Please provide a correct choice", btw, 1, 3, 25, 17, 8, 1);;
	return menuOption;
}

/**************************************/
/*                                    */
/*                SETUP               */
/*                                    */
/**************************************/

// Draw setup screen - LEFT GRID
void Game::drawSetupScreen() {
	clearInput(0, 0, 24);
	char letter = 'A';
	// Player
	print(7, 0, YELLOW, "Player");
	print(29, 0, YELLOW, "Moves");
	setColor(TEAL);
	for (int i = 0; i <= 10; ++i) {
		for (int j = 0; j <= 10; ++j) {
			// Drawing the horizontal row letters
			if ((i > 0 && i <= 10) && j == 0) {
				print(i * 2 - 1, j + 1, letter);
				print(i * 2 + 21, j + 1, letter);
				letter++;
			}
			// Drawing the vertical col numbers
			else if ((j > 0 && j <= 10) && i == 0) {
				print(i, j + 1, j - 1);
				print(i + 22, j + 1, j - 1);
			}
		}
	}

	// Computer
	DEBUG_IF(1) {
		letter = 'A';
		print(6, 13, YELLOW, "Opponent");
		print(29, 13, YELLOW, "Moves");
		setColor(TEAL);
		for (int i = 0; i <= 10; ++i) {
			for (int j = 0; j <= 10; ++j) {
				// Drawing the horizontal row letters
				if ((i > 0 && i <= 10) && j == 0) {
					print(i * 2 - 1, j + 14, letter);
					print(i * 2 + 21, j + 14, letter);
					letter++;
				}
				// Drawing the vertical col numbers
				else if ((j > 0 && j <= 10) && i == 0) {
					print(i, j + 14, j - 1);
					print(i + 22, j + 14, j - 1);
				}
			}
		}
	}

	// Water
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 10; ++j) {
			print(i + 1, j + 2, DARKTEAL, "~");
			print(i + 23, j + 2, DARKTEAL, "~");
			DEBUG_IF(1) {
				print(i + 1, j + 15, DARKTEAL, "~");
				print(i + 23, j + 15, DARKTEAL, "~");
			}
		}
	}
}

// Deciding the setup mode
int Game::setSetupMode() {

	// Resetting the ships
	setCollisionGrid();
	setAvailableShips();

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
	print(x, ++y, "Rows      (");
	print(PINK, "A - J");
	print(WHITE, ")");
	print(x, ++y, "Columns   (");
	print(PINK, "0 - 9");
	print(WHITE, ")");
	print(x, ++y, "Direction (");
	print(PINK, "Vertical");
	print(WHITE, " - ");
	print(PINK, "Horizontal");
	print(WHITE, ")");
	print(x, y += 2, GREEN, "IN GAME:");
	print(x, ++y, "Destroy your opponent's ships.");
	print(x, ++y, "Guess a position e.g. A0, B7, D4");
	print(x, ++y, "If there's a ship, it will hit it");
	print(x, ++y, "marking the ");
	print(RED, "spot ");
	print(WHITE, "where it was hit.");
	print(x, y += 2, "The opponent can hit you as well.");
	print(x, y += 2, GREEN, "SELECT SETUP METHOD (ESC to exit)");
	print(x, ++y, PINK, "1)");
	print(WHITE, " Automatic - ");
	print(PINK, "2)");
	print(WHITE, " Manual");
	print(x, ++y, "Type your option and press ");
	print(GREEN, "RETURN");
	print(x, ++y, "Option");
	print(GREEN, "> ");
	x = 52;

	// Reading our sort value (1: auto | 2: manual)
	setupMode = stringToInt(inputSort, "Please provide a correct option", eq, 1, 2, x, y, 8, 1);

	if (setupMode != -1) {
		return setupMode;
	}
	else {
		clearInput(0, 0, 24);
		setState("!X");
		return 0;
	}
}

// Get sort mode
int Game::getSetupMode() const {
	return setupMode;
}

// Print available ships
void Game::printAvailableShips() {
	setColor(WHITE);
	print(44, 0, "Available ships (ESC to exit)");
	for (int i = 0; i < 5; ++i) {
		if (currentPlayerShip[i] == 0) {
			print(44, i + 1, GREEN, std::to_string(i + 1));
			print(WHITE, ") " + SHIP_NAME[i] + "- (");
			print(GREEN, getShipCode(i));
			print(WHITE, ") - Size: ");
			print(GREEN, std::to_string(getShipSize(i)));
		}
		else {
			print(44, i + 1, std::to_string(i + 1) + ") ");
			print(RED, "ALEADY PLACED");
		}
	}
}

// Automatic sort
void Game::sortAuto() {
	while (getPlacedShips(0) > 0) {
		createShipAuto(0);
	}
	while (getPlacedShips(1) > 0) {
		createShipAuto(1);
	}
	setState("!X");
}

// Manual sort
void Game::sortManual() {
	int x = 44;
	// We want to check if either the player and computer have available ships to place
	while (getPlacedShips(0) > 0) {

		clearInput(44, 0, 24);
		printAvailableShips();

		while (true) {
			print(x, 7, "Select a ship to place");
			print(GREEN, ">");
			shipModel = stringToInt(inputShip, "Provide a correct option", outNIR, 0, 5, x + 24, 7, 24, 1);
			if (shipModel == -1) {
				setState("~/.");
				//clearInput(0, 0, 24);
				return;
			}
			if (currentPlayerShip[shipModel - 1] == 1) {
				print(x + 24, 7, " ");
				print(x, 8, PINK, "> Ship already used");
			}
			else {
				break;
			}
		}
		createShipManual();
	}
	while (getPlacedShips(1) > 0) {
		createShipAuto(1);
	}
	setState("!X");

}

// Creating a ship (AUTOMATIC)
void Game::createShipAuto(int player) {

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
	drawShip(tempDir, tempRow, tempCol, tempShip, player);
}

// Creating a ship (MANUAL)
void Game::createShipManual() {
	// Vertical screen navigation
	int x = 44;
	int y = 7;
	// Since arrays are counted starting from 0
	int SHIP_ID = shipModel - 1;

	print(x, ++y, WHITE, "Selected ");
	print(GREEN, SHIP_NAME[SHIP_ID]);
	cout << "(";
	print(GREEN, getShipCode(SHIP_ID));
	cout << ")";
	print(x, ++y, "It has a size of...........");
	setColor(GREEN);
	cout << getShipSize(SHIP_ID);
	setColor(WHITE);

	// Gettings rows and columns
	getCoordinate(inputRow, inputCol, row, col, x, y += 2);

	if (getState() == "X") {
		return;
	}

	drawShip(dir, row, col, SHIP_ID, 0);
}

// Setting rows, column and direction
void Game::getCoordinate(string& inputRow, string& inputCol, int& row, int& col, int x, int y) {

	setState("!X");
	setColor(WHITE);

	// Rows (HORIZONTAL)
	while (true) {
		print(x, y, "> Select row ("); 
		print(PINK, "A - J");
		print(WHITE, ")");
		print(GREEN, "> ");
		inputRow = readLimitedInput(x + 22, y);
		if (inputRow >= "A" && inputRow <= "J") {
			char charToInt = inputRow[0];
			row = charToInt - 65;

			clearInput(44, y + 1, y + 1);

			break;
		}
		else {
			setColor(WHITE);
			print(x + 22, y, " ");
			print(x, y + 1, "Provide a correct option");
		}
	} // Row loop

	// Column (VERTICAL)
	y += 2;
	setColor(WHITE);
	while (true) {
		print(x, y, "> Select column (");
		print(PINK, "0 - 9");
		print(WHITE, ")");
		print(GREEN, "> ");
		col = stringToInt(inputCol, "Provide a correct option", btw, 0, 9, x + 25, y, 25, 1);

		if (!(col == -1)) {
			clearInput(44, y + 1, y + 1);
			break;
		}
		else {
			setColor(WHITE);
			print(x + 25, y, " ");
			print(x, y + 1, "Provide a correct option");
		}
	} // Column loop

	// Direction (for manual setup)
	if (getSetupMode() == 2) {
		y += 2;
		setColor(WHITE);
		while (true) {
			print(x, y, "Direction");
			print(x, y + 1, PINK, "V");
			print(WHITE, "(ertical) - ");
			print(PINK, "H");
			print(WHITE, "(orizontal)");
			print(GREEN, "> ");
			inputDir = readLimitedInput(x + 27, y + 1);

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
				setColor(WHITE);
				print(x + 27, y + 1, " ");
				print(x, y + 2, "Provide a correct option");
			}
		}
		y++;
	} // Direction loop

	// Confirming placement before doing anything else
	y += 2;
	setColor(WHITE);
	while (true) {
		print(x, y,  "Confirm placing (");
		print(PINK,  "Y");
		print(WHITE, "/");
		print(PINK,  "N");
		print(WHITE, ")");
		print(GREEN, "> ");
		confirmPlacement = readLimitedInput(x + 23, y);

		if (confirmPlacement == "N") {
			return;
		}
		else if (!(confirmPlacement == "N" || confirmPlacement == "Y")) {
			setColor(WHITE);
			print(x + 23, y, " ");
			print(x, y + 1, "Provide a correct option");
		}
		else {
			break;
		}
	} // Confirmation loop

}

// Generating a random coordinate for the computer
void Game::randomCoordinate(int currentTurn, int & row, int & col, int x, int y) {

	bool foundHit = false;

	while (true) {

		char charToString;

		//for (int i = 0; i < 10; ++i) {

		//	for (int j = 0; j < 10; ++j) {

		//		if (playerHitGrid[i][j] == 1) {

		//			foundHit = true;

		//			// Case 1
		//			if ((rand() % 2) % 2 == 0) {

		//				if ((rand() % 2) % 2 == 0) {
		//					row = i + 1;
		//				}
		//				else {
		//					row = i - 1;
		//				}

		//				col = j;

		//				break;
		//			}
		//			// Case 2
		//			else {
		//				if ((rand() % 2) % 2 == 0) {
		//					col = j + 1;
		//				}
		//				else {
		//					col = j - 1;
		//				}

		//				row = i;

		//				break;
		//			}

		//		}

		//	} // FOR J

		//	if (foundHit == true) {

		//		charToString = row + 65;
		//		inputRow[0] = charToString;
		//		break;
		//	}

		//} // FOR I

		//if (foundHit == false) {

		//	row = rand() % 10;
		//	col = rand() % 10;

		//	if ((playerHitGrid[row][col] == 1) || (playerMissGrid[row][col] == 1)) {
		//		row = rand() % 10;
		//		col = rand() % 10;
		//	}
		//	else {
		//		charToString = row + 65;
		//		inputRow[0] = charToString;
		//		//break;
		//	}
		//}


		//break;

		// Chance 1
		//if ((rand() % 2) % 2 == 0) {
			row = rand() % 10;
			col = rand() % 10;

			if ((playerHitGrid[row][col] == 1) || (playerMissGrid[row][col] == 1)) {
				row = rand() % 10;
				col = rand() % 10;
			}
			else {
				charToString = row + 65;
				inputRow[0] = charToString;
				break;
			}

		//}
		//// Chance 2
		//else {
		//	// Chance 2.1
		//	if ((rand() % 2) % 2 == 0) {
		//		int i = 0;
		//		int j = 0;

		//		for (i; i < 10; ++i) {
		//			for (j; j < 10; ++j) {
		//				if (playerHitGrid[i][j] == 1) {
		//					row = i;
		//					col = j;
		//					break;
		//				}
		//			} // j
		//			if ((row == i)) {
		//				charToString = row + 65;
		//				inputRow[0] = charToString;
		//				break;
		//			}
		//		} // i
		//	} // Chance 2.1
		//	// Chance 2.2
		//	else {
		//		int i = 9;
		//		int j = 9;

		//		for (i; i >= 0; --i) {
		//			for (j; j >= 0; --j) {
		//				if (playerHitGrid[i][j] == 1) {
		//					row = i;
		//					col = j;
		//					break;
		//				}
		//				else if (playerMissGrid[i][j] == 1) {

		//				}
		//			} // j
		//			if ((row == i)) {
		//				charToString = row + 65;
		//				inputRow[0] = charToString;
		//				break;
		//			}
		//		} // i
		//	} // Chance 2.2
		//} // Chance 2
			// If it's already been hit or missed, we 're-roll' coordinates
			// If the place he's searching for has been hit, move 1 position up or down
			/*if (playerHitGrid[row][col] == 1) {
				if ((rand() % 2) % 2 == 0) {
					
					if ((rand() % 2) % 2 == 0) {
						row++;
					}
					else {
						col++;
					}

				}
				else {
					row = rand() % 10;
					col = rand() % 10;
				}
			}
			else {
				charToString = row + 65;
				inputRow[0] = charToString;
				break;
			}*/
	}
}

// Placing the ships for the player and the AI
void Game::drawShip(int dir, int row, int col, int SHIP_ID, int player) {

	// Possible directions (dir)
	// 1: VERTICAL
	// 0: HORIZONTAL

	int position;
	int currentGridPos;
	int outOfBoundsPos;

	if (dir == 1) {
		position = col;
	}
	else {
		position = row;
	}

	// Collision checking (includes out of bounds)
	for (int tempPos = position; tempPos < getShipSize(SHIP_ID) + position; ++tempPos) {

		// Vertical	
		if (dir == 1) {
			if (player == 0) {
				currentGridPos = playerGrid[row][tempPos];
				outOfBoundsPos = playerGrid[row][tempPos + 1];
			}
			else {
				currentGridPos = computerGrid[row][tempPos];
				outOfBoundsPos = computerGrid[row][tempPos + 1];
			}
		}
		// Horizontal
		else {
			if (player == 0) {
				currentGridPos = playerGrid[tempPos][col];
				outOfBoundsPos = playerGrid[tempPos + 1][col];
			}
			else {
				currentGridPos = computerGrid[tempPos][col];
				outOfBoundsPos = computerGrid[tempPos + 1][col];
			}
		}

		// Out of bounds
		if (tempPos >= 9 && outOfBoundsPos == 1) {
			if (getSetupMode() == 2 && player == 0) {
				tempPos -= 2;
				print(44, 20, GREEN, "####  ");
				print(WHITE, "OUT OF BOUNDS");
				print(GREEN, "  ####");
				print(44, 21, GREEN, "####    ");
				print(WHITE, "TRY AGAIN");
				print(GREEN, "    ####");
				Sleep(1500);
			}
			return;
		}

		// Position has been taken
		if ((currentGridPos >= 1) && (currentGridPos <= 5)) {
			spaceTaken = true;
			if (getSetupMode() == 2 && player == 0) {
				print(44, 20, GREEN, "##  ");
				print(WHITE, "Position " + inputRow + "-" + std::to_string(tempPos) + " occupied");
				print(GREEN, "  ##");
				print(44, 21, GREEN, "##       ");
				print(WHITE, "TRY AGAIN");
				print(GREEN, "         ##");
				Sleep(1500);
			}
			break;
		}
	}

	// If there aren't any taken spaces, we place the desired ship accordingly
	if (spaceTaken == false) {
		for (int tempPosition = position; tempPosition < getShipSize(SHIP_ID) + position; ++tempPosition) {
			/// Vertical
			if (dir == 1) {
				// Player
				if (player == 0) {
					playerGrid[row][tempPosition] = SHIP_ID + 1;
					print(row * 2 + 1, tempPosition + 2, GREEN, getShipCode(SHIP_ID));
				}
				// Computer
				else {
					computerGrid[row][tempPosition] = SHIP_ID + 1;
					DEBUG_IF(1) {
						print(row * 2 + 1, tempPosition + 15, GREEN, getShipCode(SHIP_ID));
					}
				}
			}
			/// Horizontal
			else {
				// Player
				if (player == 0) {
					playerGrid[tempPosition][col] = SHIP_ID + 1;
					print(tempPosition * 2 + 1, col + 2, GREEN, getShipCode(SHIP_ID));
				}
				// Computer
				else {
					computerGrid[tempPosition][col] = SHIP_ID + 1;
					DEBUG_IF(1) {
						print(tempPosition * 2 + 1, col + 15, GREEN, getShipCode(SHIP_ID));
					}
				}
			}
		}
		/// Making the ship unavailable now that it has been placed
		// Player
		if (player == 0)
			currentPlayerShip[SHIP_ID] = 1;
		// Computer
		else if (player == 1)
			currentComputerShip[SHIP_ID] = 1;

		// Add to the corresponding's player ship counter
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

// Drawing the game screen - MIDDLE GRID
void Game::drawGameScreen() {
	// Since everything else is drawn in the setup method, 
	// we just need to clear the right side of the screen
	clearInput(44, 0, 24);
}


void Game::update() {

	// We reset our sort value otherwise it would ask for direction
	// when trying to hit a ship
	setupMode = 0;

	int x = 44;
	int y = 0;
	
	// Reminder for ship sizes and codes
	drawShipInfo(x, y);

	// Will continue to ask for hits until a winner has been chosen
	while (!(hitCounter[turn % 2] == 17)) {

		// Clearing previous text
		clearInput(x, 0, 10);

		/// Player
		if (turn % 2 == 0) {

			print(x, y, YELLOW, "> YOUR TURN");
			print(x, y + 1, GREEN, "Pick a position e.g. A-4, F-8, C-6");
			print(x, y + 2, GREEN, "Try to hit your opponent's ships!");
			inputRow = "~/.";
			while (true) {

				// Getting a coordinate to hit
				getCoordinate(inputRow, inputCol, row, col, x, y + 3);

				// Making sure we don't hit the same position twice
				if (confirmPlacement == "Y") {
					if ((computerHitGrid[row][col] == 1) || (computerMissGrid[row][col] == 1)) {
						print(x, y + 9, RED, "Position already hit. Try again");
						print(x + 22, y + 3, " ");
						print(x + 25, y + 5, " ");
						print(x + 23, y + 7, " ");
					}
					else {
						break;
					}
				}
				else {
					clearInput(x, 3, 10);
				}
			} // while loop
		}
		/// Computer
		else {
			print(x, y, YELLOW, "> OPPONENT'S TURN");
			randomCoordinate(1, row, col, x, y + 1);
		}

		// Clearing previous text
		clearInput(x, 1, 9);

		// Printing the hit calls
		if (turn % 2 == 0) {
			print(x, y + 2, GREEN, "> You call " + inputRow + "-" + std::to_string(col));
		}
		else {
			print(x, y + 2, GREEN, "> Opponent calls " + inputRow + "-" + std::to_string(col));
		}

		// Checking for collisions
		checkHit(row, col, turn);
		// Asking for confirmation to continue
		confirmRETURN(x, y + 6);

		// Asks if wants to keep playing
		if (turn % 2 != 0) {

			clearInput(x, 0, 9);

			setColor(WHITE);
			while (true) {
				print(x, y + 1, "> Continue playing? (");
				print(PINK, "Y");
				print(WHITE, "/");
				print(PINK, "N");
				print(WHITE, ")");
				print(GREEN, "> ");
				continuePlaying = readLimitedInput(x + 27, y + 1);

				if (continuePlaying == "N") {
					return;
				}
				else if (!((continuePlaying == "N") || (continuePlaying == "Y"))) {
					setColor(WHITE);
					print(x + 27, y + 1, " ");
					print(x, y + 2, "Provide a correct option");
				}
				else {
					break;
				}
			} // !Confirmation loop
		}

		// Next turn
		turn++;

	} // !while loop

	// Now that we found a winner, we display it
	getWinner(turn % 2);

}

// Checking which player has been hit
void Game::checkHit(int row, int col, int currentTurn) {

	/// Player
	if (turn % 2 == 0) {

		// Hit
		if (computerGrid[row][col] >= 1 && computerGrid[row][col] <= 5) {
			
			computerHitGrid[row][col] = 1;

			if (hasBeenSunk(computerGrid[row][col] - 1, row, col, turn % 2) == true) {
				print(44, 4, RED, "> Sunk opponent's " + SHIP_NAME[computerGrid[row][col] - 1]);
			}
			else {
				print(44, 4, RED, "> You hit " + SHIP_NAME[computerGrid[row][col] - 1]);
			}

			print(row * 2 + 23, col + 2, RED, getShipCode(computerGrid[row][col] - 1));
			hitCounter[turn % 2]++;
		}
		// Miss
		else {
			print(44, 4, PINK, "> You missed your shot!");
			computerMissGrid[row][col] = 1;
			print(row * 2 + 23, col + 2, DARKPINK, 'o');
		}

	} // Player
	/// Computer
	else if (turn % 2 == 1) {

		// Hit
		if (playerGrid[row][col] >= 1 && playerGrid[row][col] <= 5) {
			
			playerHitGrid[row][col] = 1;

			if (hasBeenSunk(playerGrid[row][col] - 1, row, col, turn % 2) == true) {
				print(44, 4, RED, "> Opponent sunk your " + SHIP_NAME[playerGrid[row][col] - 1]);
			}
			else {
				print(44, 4, RED, "> Opponent hits " + SHIP_NAME[playerGrid[row][col] - 1]);
			}

			hasFoundShip = true;
			DEBUG_IF(1) {
				print(row * 2 + 23, col + 15, RED, getShipCode(playerGrid[row][col] - 1));
			}
			hitCounter[turn % 2]++;
		}
		// Miss
		else {
			print(44, 4, PINK, "> Your opponent missed!");
			playerMissGrid[row][col] = 1;
			DEBUG_IF(1) {
				print(row * 2 + 23, col + 15, DARKPINK, 'o');
			}
		}

	} // Computer
}

// Checking for which ship has been sunk
bool Game::hasBeenSunk(int shipCode, int row, int col, int turn) {

	shipSizeCounter = 0;

	for (int i = 0; i < 10; ++i) {

		for (int j = 0; j < 10; ++j) {

			// Player
			if (turn % 2 == 0) {

				if ((computerGrid[i][j] == shipCode + 1) && (computerHitGrid[i][j] == 1)) {
					shipSizeCounter++;
				}

			}
			// Computer
			else {

				if ((playerGrid[i][j] == shipCode + 1) && (playerHitGrid[i][j] == 1)) {
					shipSizeCounter++;
				}

			}

		}

	}

	if (shipSizeCounter == getShipSize(shipCode)) {
		return true;
	}
	else {
		return false;
	}

}

// Display winner and message
void Game::getWinner(int currentPlayer) {
	clearInput(44, 0, 24);
	if (currentPlayer == 0) {
		print(44, 1, YELLOW, "> YOU WIN!");
	}
	else {
		print(44, 1, YELLOW, "> COMPUTER WINS!");
	}
	gotoxy(44, 11, true);
	confirmRETURN(44, 3);
}

// Drawing ship information
void Game::drawShipInfo(int x, int y) {
	print(x + 10, y + 18, GREEN, "SHIP INFORMATION");

	// Ship info
	for (int i = 0; i < 5; ++i) {
		print(x + 2, y + 19 + i, SHIP_NAME[i] + "- (");
		print(RED, getShipCode(i));
		print(WHITE, ") - Size ");
		print(RED, std::to_string(getShipSize(i)));
	}

	// Borders
	for (int i = x; i < 79; ++i) {
		for (int j = 0; j <= 7; ++j) {

			if ((i == x || i == 78) && (j > 0 && j < 7))
				print(i, y + 17 + j, "|");
			if ((j == 0 || j == 7) && (i > 0 && i < 79))
				print(i, y + 17 + j, "=");

		}
	}
}

/**************************************/
/*                                    */
/*             GAME OVER              */
/*                                    */
/**************************************/

// Drawing game over screen
void Game::drawGameOverScreen() {
	clearInput(0, 0, 24);

	drawScreenBorders();

	int x = 17;
	int y = 5;
	// Text
	print(x, y, TEAL, "___  ____ ___ ___ _    ____ ____ _  _ _ ___ ");
	print(x, ++y, TEAL, "|__] |__|  |   |  |    |___ [__  |__| | |__]");
	print(x, ++y, TEAL, "|__] |  |  |   |  |___ |___ ___] |  | | |   ");
	y += 8;
	print(x, y,   "> PLAY AGAIN?");
	print(x, ++y, "");
	print(PINK,   "Y");
	print(WHITE,  "(es)/ ");
	print(PINK,   "N");
	print(WHITE,  "(no)");
	print(x, ++y, "Type your option and press ");
	print(GREEN,  "ENTER / RETURN");
	print(x, ++y, "Option");
	print(GREEN,  "> ");
}

// Asks if player wants to keep playing
string Game::setGameOver() {
	while (true) {
		confirmExit = readLimitedInput(25, 18);
		if (confirmExit != "Y" && confirmExit != "N") {
			setColor(WHITE);
			print(25, 18, " ");
			print(17, 19, "Please provide a correct option");
		}
		else {
			break;
		}
	}
	clearInput(0, 0, 24);
	return confirmExit;
}

/**************************************/
/*                                    */
/*           QUIT / CREDITS           */
/*                                    */
/**************************************/

// Drawing the ending screen
void Game::drawQuitScreen() {

	drawScreenBorders();

	int x = 5;
	int y = 0;

	setColor(YELLOW);

	print(x, ++y, ".___________. __    __       ___      .__   __.  __  ___      _______.  ");
	print(x, ++y, "|           ||  |  |  |     /   \\     |  \\ |  | |  |/  /     /       |");
	print(x, ++y, "`---|  |----`|  |__|  |    /  ^  \\    |   \\|  | |  '  /     |   (----`");
	print(x, ++y, "    |  |     |   __   |   /  /_\\  \\   |  . `  | |    <       \\   \\  ");
	print(x, ++y, "    |  |     |  |  |  |  /  _____  \\  |  |\\   | |  .  \\  .----)   |  ");
	print(x, ++y, "    |__|     |__|  |__| /__/     \\__\\ |__| \\__| |__|\\__\\ |_______/ ");
	x = 24;
	++y;
	print(x, ++y, " _______   ______   .______      ");
	print(x, ++y, "|   ____| /  __  \\  |   _  \\     ");
	print(x, ++y, "|  |__   |  |  |  | |  |_)  |    ");
	print(x, ++y, "|   __|  |  |  |  | |      /     ");
	print(x, ++y, "|  |     |  `--'  | |  |\\  \\----.");
	print(x, ++y, "|__|      \\______/  | _| `._____|");
	x = 5;
	++y;
	print(x, ++y, ".______   __          ___   ____    ____  __  .__   __.   _______  __  ");
	print(x, ++y, "|   _  \\ |  |        /   \\  \\   \\  /   / |  | |  \\ |  |  /  _____||  | ");
	print(x, ++y, "|  |_)  ||  |       /  ^  \\  \\   \\/   /  |  | |   \\|  | |  |  __  |  | ");
	print(x, ++y, "|   ___/ |  |      /  /_\\  \\  \\_    _/   |  | |  . `  | |  | |_ | |  | ");
	print(x, ++y, "|  |     |  `----./  _____  \\   |  |     |  | |  |\\   | |  |__| | |__| ");
	print(x, ++y, "| _|     |_______/__/     \\__\\  |__|     |__| |__| \\__|  \\______| (__) ");
	x = 25;
	y += 2;
	confirmRETURN(x, y);
}

// Drawing credits
void Game::drawCreditsScreen() {
	clearInput(0, 0, 24);

	drawScreenBorders();

	int x = 25;
	int y = 3;

	setColor(WHITE);

	print(x, y += 2, "Media Design School");
	print(x, y += 2, "Auckland");
	print(x, y += 2, "New Zealand");
	y += 2;
	print(x, y += 2, "Lecturer: Bindu Ojha");
	print(x, y += 2, "Student: Juan Rodriguez");
	y += 4;
	confirmRETURN(x, y);
	clearInput(0, 0, 24);
}

// Drawing borders of the screen
void Game::drawScreenBorders() {

	setColor(GREEN);
	for (int i = 0; i < 80; ++i) {
		for (int j = 0; j <= 24; ++j) {

			// Vertical borders
			if ((j == 0 || j == 24))
				print(i, j, "#");
			// Horizontal borders
			if ((i == 0 || i == 77) && (j > 0 && j < 24))
				print(i, j, "[x]");

		}
	}
	gotoxy(0, 0, true);
}