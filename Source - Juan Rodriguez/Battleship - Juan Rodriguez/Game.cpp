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
#define IF_DEBUG(cond) if(cond)
#else
#define IF_DEBUG(cond)
#endif

// This include
#include "Game.h"

// Easier access of this 'std' functions
using std::to_string;
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

// Constructor
Game::Game() {

	/// Seeding the pseudo-random number generator
	srand((unsigned int)time(NULL));
	/// Allocating memory for our currentShips
	piCurrentPlayerShip = new int[5];
	piCurrentComputerShip = new int[5];
	/// For determining which space has been taken in order to place ships
	bSpaceTaken = false;
	/// Hit/miss counters
	// Player
	iHitCounter[0] = 0;
	// Computer
	iHitCounter[1] = 0;

}

// Destructor
Game::~Game() {

	delete[] piCurrentPlayerShip;
	delete[] piCurrentComputerShip;
	piCurrentPlayerShip = 0;
	piCurrentComputerShip = 0;

}

// sets the collision grid up
// @return void
void Game::setCollisionGrid() {

	// Player
	for (int i = 0; i < 12; ++i) {

		for (int j = 0; j < 12; ++j) {

			iPlayerGrid[i][j] = 0;
			iPlayerGrid[11][j] = 1;
			iPlayerGrid[i][11] = 1;

		}

	}
	// Computer
	for (int i = 0; i < 12; ++i) {

		for (int j = 0; j < 12; ++j) {

			iComputerGrid[i][j] = 0;
			iComputerGrid[11][j] = 1;
			iComputerGrid[i][11] = 1;

		}

	}

}

// Resets the ships
// @return void
void Game::setAvailableShips() {

	// inputRow is only used when passing it as an argument to a reference, so we must initialize it
	strInput = " ";
	// Resetting turn counter
	iTurn = 0;
	// Back to not finding ships
	bHasFoundShip = false;
	iShipDirection = 0;
	// Resetting the computer's hit row/column
	iHitRow = 0;
	iHitCol = 0;
	// Resetting current ships
	for (int i = 0; i < 5; ++i) {

		piCurrentPlayerShip[i] = 0;
		piCurrentComputerShip[i] = 0;

	}
	// Resetting hit/miss grids
	for (int i = 0; i < 10; ++i) {

		for (int j = 0; j < 10; ++j) {

			iPlayerHitGrid[i][j] = 0;
			iPlayerMissGrid[i][j] = 0;
			iComputerHitGrid[i][j] = 0;
			iComputerMissGrid[i][j] = 0;

		}

	}
	// Player ships and hit counter
	iCurrentShipsPlaced[0] = 0;
	iHitCounter[0] = 0;
	// Computer ships and hit counter
	iCurrentShipsPlaced[1] = 0;
	iHitCounter[1] = 0;

}

// Gets the currently placed ships
// @return int
int Game::getPlacedShips(int _iCode) const {

	return MAX_SHIPS - iCurrentShipsPlaced[_iCode];

}

// Checks whether or not can keep placing ships
// @return boolean
bool Game::canPlaceShips(int _ship) const {

	return (getPlacedShips(_ship) > 0);

}

// Gets the size of the ship
// @return int
int Game::getShipSize(int _iCode) const {

	if (_iCode == 0)
		return 5;
	else if (_iCode == 1)
		return 4;
	else if (_iCode == 2)
		return 3;
	else if (_iCode == 3)
		return 3;
	else if (_iCode == 4)
		return 2;
	else
		return 0;

}

// Gets the code of the ship
// @return char
char Game::getShipCode(int _iCode) const {

	if (_iCode == 0)
		return '@';
	else if (_iCode == 1)
		return '#';
	else if (_iCode == 2)
		return '&';
	else if (_iCode == 3)
		return '*';
	else if (_iCode == 4)
		return '$';
	else
		return '\0';

}

// Setting the sort mode
// @return void
void Game::setSortMode(std::string _strSortMode) {

	strCancelSort = _strSortMode;

}

// Getting the sort mode
// @return std::string
string Game::getSortMode() const {

	return strCancelSort;

}

/**************************************/
/*                                    */
/*                MENU                */
/*                                    */
/**************************************/

// Drawing the menu screen
// @return void
void Game::drawMenuScreen() {

	drawScreenBorders();
	int x = 17;
	int y = 5;
	// Text
	print(x, y, TEAL, "___  ____ ___ ___ _    ____ ____ _  _ _ ___ ");
	print(x, ++y, TEAL, "|__] |__|  |   |  |    |___ [__  |__| | |__]");
	print(x, ++y, TEAL, "|__] |  |  |   |  |___ |___ ___] |  | | |   ");
	y += 8;
	print(x, y, PINK, "1) ");
	print(WHITE, "Play          ");
	print(PINK, "2) ");
	print(WHITE, "Credits          ");
	print(PINK, "3) ");
	print(WHITE, "Exit");
	print(x, ++y, "Type your option and press ");
	print(GREEN, "RETURN");
	print(x, ++y, "Option");
	print(GREEN, "> ");
	IF_DEBUG(1) {

		print(3, 23, DARKPINK, "Debug mode");

	}

}

// Reading the option of the menu to navigate through
// @return int
int Game::setMenu() {

	int iMenuOption;
	iMenuOption = stringToInt(strInput, "Please provide a correct choice", btw, 1, 3, 25, 17, 8, 1);;
	return iMenuOption;

}

/**************************************/
/*                                    */
/*                SETUP               */
/*                                    */
/**************************************/

// Draw setup screen - LEFT GRID
// @return void
void Game::drawSetupScreen() {

	clearInput(0, 0, 24);
	cLetter = 'A';
	// Player
	print(7, 0, YELLOW, "Player");
	print(29, 0, YELLOW, "Moves");
	setColor(TEAL);
	for (int i = 0; i <= 10; ++i) {

		for (int j = 0; j <= 10; ++j) {

			// Drawing the horizontal row letters
			if ((i > 0 && i <= 10) && j == 0) {

				print(i * 2 - 1, j + 1, cLetter);
				print(i * 2 + 21, j + 1, cLetter);
				cLetter++;

			}
			// Drawing the vertical col numbers
			else if ((j > 0 && j <= 10) && i == 0) {

				print(i, j + 1, j - 1);
				print(i + 22, j + 1, j - 1);

			}

		}

	}

	// Computer
	IF_DEBUG(1) {

		cLetter = 'A';
		print(6, 13, YELLOW, "Opponent");
		print(29, 13, YELLOW, "Moves");
		setColor(TEAL);
		for (int i = 0; i <= 10; ++i) {

			for (int j = 0; j <= 10; ++j) {

				// Drawing the horizontal row letters
				if ((i > 0 && i <= 10) && j == 0) {

					print(i * 2 - 1, j + 14, cLetter);
					print(i * 2 + 21, j + 14, cLetter);
					cLetter++;

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

			if (i < 10) {

				print(i * 2 + 23, j + 2, DARKTEAL, "~");

			}
			IF_DEBUG(1) {

				print(i + 1, j + 15, DARKTEAL, "~");

				if (i < 10) {

					print(i * 2 + 23, j + 15, DARKTEAL, "~");

				}

			}

		}

	}

}

// Deciding the setup mode
// @return void
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
	iSetupMode = stringToInt(strInput, "Please provide a correct option", eq, 1, 2, x, y, 8, 1);
	if (iSetupMode != -1) {

		return iSetupMode;

	}
	else {

		clearInput(0, 0, 24);
		setSortMode("!X");
		return 0;

	}

}

// Get sort mode
// @return void
int Game::getSetupMode() const {

	return iSetupMode;

}

// Print available ships
// @return void
void Game::printAvailableShips() {

	setColor(WHITE);
	print(44, 0, "Available ships (ESC to exit)");
	for (int i = 0; i < 5; ++i) {

		if (piCurrentPlayerShip[i] == 0) {

			print(44, i + 1, GREEN, to_string(i + 1));
			print(WHITE, ") " + SHIP_NAME[i] + "- (");
			print(GREEN, getShipCode(i));
			print(WHITE, ") - Size: ");
			print(GREEN, to_string(getShipSize(i)));

		}
		else {

			print(44, i + 1, to_string(i + 1) + ") ");
			print(RED, "ALEADY PLACED");

		}

	}

}

// Automatic sort
// @return void
void Game::sortAutomatic() {

	while (getPlacedShips(0) > 0) {

		setShipAuto(0);

	}
	while (getPlacedShips(1) > 0) {

		setShipAuto(1);

	}
	setSortMode("!X");

}

// Manual sort
// @return void
void Game::sortManual() {

	int x = 44;
	// We want to check if either the player and computer have available ships to place
	while (getPlacedShips(0) > 0) {

		clearInput(44, 0, 24);
		printAvailableShips();

		while (true) {

			print(x, 7, "Select a ship to place");
			print(GREEN, ">");
			iShipModel = stringToInt(strInput, "Provide a correct option", outNIR, 0, 5, x + 24, 7, 24, 1);
			if (iShipModel == -1) {

				setSortMode("X");
				return;

			}
			if (piCurrentPlayerShip[iShipModel - 1] == 1) {

				print(x + 24, 7, " ");
				print(x, 8, PINK, "> Ship already used");

			}
			else {

				break;

			}

		}

		setShipManual();

	}
	while (getPlacedShips(1) > 0) {

		setShipAuto(1);

	}
	setSortMode("!X");

}

// Creating a ship (AUTOMATIC)
// @return void
void Game::setShipAuto(int _iPlayer) {

	int tempShip = rand() % 5;
	int tempRow = rand() % 10;
	int tempCol = rand() % 10;
	int tempDir = rand() % 2;

	// Checking whether or not the ship is available for use
	while (true) {

		if (_iPlayer == 0 || _iPlayer == 1) {

			if (_iPlayer == 0) {

				if (piCurrentPlayerShip[tempShip] == 1) {

					tempShip = rand() % 5;

				}
				else {

					break;

				}
			}
			else if (_iPlayer == 1) {

				if (piCurrentComputerShip[tempShip] == 1) {

					tempShip = rand() % 5;

				}
				else {

					break;

				}
			}

		}

	}

	createShip(tempDir, tempRow, tempCol, tempShip, _iPlayer);

}

// Creating a ship (MANUAL)
// @return void
void Game::setShipManual() {

	// Vertical screen navigation
	int x = 44;
	int y = 7;
	// Since arrays are counted starting from 0
	int SHIP_ID = iShipModel - 1;

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
	setFireCoordinates(strInput, iRow, iCol, x, y += 2);

	if (getSortMode() == "X") {

		return;

	}

	createShip(cDir, iRow, iCol, SHIP_ID, 0);

}

// Setting rows, column and direction
// @param _rStrInput the string to read (this one needs conversion)
// @param _rStrInputCol the string of the column to read
// @param _riRow the row to fire at
// @param _riCol the column to fire at
// @param _iX the 'x' coordinate to print at
// @param _iY the 'y' coordinate to print at
// @return void
void Game::setFireCoordinates(std::string& _rStrInput, int& _riRow, int& _riCol, int _iX, int _iY) {

	setSortMode("!X");
	int tempY = _iY;

	while (true) {

		setColor(WHITE);
		_iY = tempY;

		// Rows (HORIZONTAL)
		while (true) {

			print(_iX, _iY, "> Select row (");
			print(PINK, "A - J");
			print(WHITE, ")");
			print(GREEN, "> ");
			_rStrInput = readLimitedInput(_iX + 22, _iY);
			if (_rStrInput >= "A" && _rStrInput <= "J") {

				clearInput(44, _iY + 1, _iY + 1);
				char charToInt = _rStrInput[0];
				_riRow = charToInt - 65;
				break;

			}
			else {

				setColor(WHITE);
				print(_iX + 22, _iY, " ");
				print(_iX, _iY + 1, "Provide a correct option");

			}

		} // Row loop

		// Column (VERTICAL)
		_iY += 2;
		setColor(WHITE);
		while (true) {

			print(_iX, _iY, "> Select column (");
			print(PINK, "0 - 9");
			print(WHITE, ")");
			print(GREEN, "> ");
			_riCol = stringToInt(_rStrInput, "Provide a correct option", btw, 0, 9, _iX + 25, _iY, 25, 1);

			if (!(_riCol == -1)) {

				clearInput(44, _iY + 1, _iY + 1);
				break;

			}
			else {

				setColor(WHITE);
				print(_iX + 25, _iY, " ");
				print(_iX, _iY + 1, "Provide a correct option");

			}

		} // Column loop

		  // Direction (for manual setup)
		if (getSetupMode() == 2) {

			_iY += 2;
			setColor(WHITE);
			while (true) {

				print(_iX, _iY, "Direction");
				print(_iX, _iY + 1, PINK, "V");
				print(WHITE, "(ertical) - ");
				print(PINK, "H");
				print(WHITE, "(orizontal)");
				print(GREEN, "> ");
				_rStrInput = readLimitedInput(_iX + 27, _iY + 1);

				if (_rStrInput == "V" || _rStrInput == "H") {

					if (_rStrInput == "V") {

						cDir = 1;
					
					}
					else if (_rStrInput == "H") {

						cDir = -1;

					}

					for (int i = 44; i < 80; ++i) {

						print(i, _iY + 2, " ");

					}

					break;

				}
				else {

					setColor(WHITE);
					print(_iX + 27, _iY + 1, " ");
					print(_iX, _iY + 2, "Provide a correct option");

				}

			}

			_iY++;

		} // Direction loop

		  // Confirming placement before doing anything else
		_iY += 2;
		setColor(WHITE);
		while (true) {

			print(_iX, _iY, "Confirm placing (");
			print(PINK, "Y");
			print(WHITE, "/");
			print(PINK, "N");
			print(WHITE, ")");
			print(GREEN, "> ");
			_rStrInput = readLimitedInput(_iX + 23, _iY);

			if (_rStrInput == "N") {

				print(66, 11, " ");
				print(69, 13, " ");
				print(71, 16, " ");
				print(67, 18, " ");
				break;

			}
			else if (!(_rStrInput == "N" || _rStrInput == "Y")) {

				setColor(WHITE);
				print(_iX + 23, _iY, " ");
				print(_iX, _iY + 1, "Provide a correct option");

			}
			else {

				return;

			}

		} // Confirmation loop

	}

}

// Placing the ships for the player and the AI
// @param _iDir the direction to place it
// @param _iRow the starting row
// @param _iCol the starting column
// @param _iShipID the ID of the ship that's about to be created
// @param _iPlayer the current player
// @return void
void Game::createShip(int _iDir, int _iRow, int _iCol, int _iShipID, int _iPlayer) {

	int position;
	int currentGridPos;
	int outOfBoundsPos;

	if (_iDir == 1) {

		position = _iCol;

	}
	else {

		position = _iRow;

	}

	// Collision checking (includes out of bounds)
	for (int tmp = position; tmp < getShipSize(_iShipID) + position; ++tmp) {

		// Vertical	
		if (_iDir == 1) {

			if (_iPlayer == 0) {

				currentGridPos = iPlayerGrid[_iRow][tmp];
				outOfBoundsPos = iPlayerGrid[_iRow][tmp + 1];

			}
			else {

				currentGridPos = iComputerGrid[_iRow][tmp];
				outOfBoundsPos = iComputerGrid[_iRow][tmp + 1];

			}

		}
		// Horizontal
		else {
			if (_iPlayer == 0) {

				currentGridPos = iPlayerGrid[tmp][_iCol];
				outOfBoundsPos = iPlayerGrid[tmp + 1][_iCol];

			}
			else {

				currentGridPos = iComputerGrid[tmp][_iCol];
				outOfBoundsPos = iComputerGrid[tmp + 1][_iCol];

			}

		}

		// Out of bounds
		if (tmp >= 9 && outOfBoundsPos == 1) {

			if (getSetupMode() == 2 && _iPlayer == 0) {

				tmp -= 2;
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

			bSpaceTaken = true;
			if (getSetupMode() == 2 && _iPlayer == 0) {

				print(44, 20, GREEN, "##  ");
				print(WHITE, "Position " + strInput + "-" + to_string(tmp) + " occupied");
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
	if (bSpaceTaken == false) {

		for (int tmp = position; tmp < getShipSize(_iShipID) + position; ++tmp) {
			/// Vertical
			if (_iDir == 1) {
				// Player
				if (_iPlayer == 0) {

					iPlayerGrid[_iRow][tmp] = _iShipID + 1;
					print(_iRow * 2 + 1, tmp + 2, GREEN, getShipCode(_iShipID));

				}
				// Computer
				else {

					iComputerGrid[_iRow][tmp] = _iShipID + 1;
					IF_DEBUG(1) {

						print(_iRow * 2 + 1, tmp + 15, GREEN, getShipCode(_iShipID));

					}

				}

			}
			/// Horizontal
			else {
				// Player
				if (_iPlayer == 0) {

					iPlayerGrid[tmp][_iCol] = _iShipID + 1;
					print(tmp * 2 + 1, _iCol + 2, GREEN, getShipCode(_iShipID));

				}
				// Computer
				else {

					iComputerGrid[tmp][_iCol] = _iShipID + 1;
					IF_DEBUG(1) {

						print(tmp * 2 + 1, _iCol + 15, GREEN, getShipCode(_iShipID));

					}

				}

			}

		}
		/// Making the ship unavailable now that it has been placed
		// Player
		if (_iPlayer == 0) {

			piCurrentPlayerShip[_iShipID] = 1;

		}
		// Computer
		else if (_iPlayer == 1) {
	
			piCurrentComputerShip[_iShipID] = 1;

		}

		// Add to the corresponding's player ship counter
		iCurrentShipsPlaced[_iPlayer]++;

	}
	else {

		bSpaceTaken = false;

	}

}

/**************************************/
/*                                    */
/*                GAME                */
/*                                    */
/**************************************/

// Drawing the game screen - MIDDLE GRID
// @return void
void Game::drawGameScreen() {
	// Since everything else is drawn in the setup method, 
	// we just need to clear the right side of the screen
	clearInput(44, 0, 24);
}

// Gameplay loop
// @return void
void Game::updateGame() {

	// We reset our sort value otherwise it would ask for direction
	// when trying to hit a ship
	iSetupMode = 0;
	int x = 44;
	int y = 0;
	// Reminder for ship sizes and codes
	drawShipInfo(x, y);

	// Will continue to ask for hits until a winner has been chosen
	while (true) {

		// Clearing previous text
		clearInput(x, 0, 10);

		/// Player
		if (iTurn % 2 == 0) {

			print(x, y, YELLOW, "> YOUR TURN");
			print(x, y + 1, GREEN, "Pick a position e.g. A-4, F-8, C-6");
			print(x, y + 2, GREEN, "Try to hit your opponent's ships!");

			while (true) {

				// Getting a coordinate to hit
				setFireCoordinates(strInput, iRow, iCol, x, y + 3);

				// Making sure we don't hit the same position twice
				if (strInput == "Y") {

					if ((iComputerHitGrid[iRow][iCol] == 1) || (iComputerMissGrid[iRow][iCol] == 1)) {

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

			} // !while loop

		}
		/// Computer
		else {

			print(x, y, YELLOW, "> OPPONENT'S TURN");
			if (bHasFoundShip == true) {

				setRandomCoordinates(1, iHitRow, iHitCol);

			}
			else {

				setRandomCoordinates(1, iRow, iCol);

			}
		}

		// Clearing previous text
		clearInput(x, 1, 9);

		// Printing the hit calls
		if (iTurn % 2 == 0) {

			print(x, y + 2, GREEN, "> You call " + strInput + "-" + to_string(iCol));

		}
		else {

			print(x, y + 2, GREEN, "> Opponent calls " + strInput + "-" + to_string(iCol));

		}

		// Checking if has hit a position
		checkForHit(iRow, iCol, iTurn);

		// Asking for confirmation to continue
		confirmRETURN(x, y + 6);

		// Asks if wants to keep playing
		if (iTurn % 2 != 0) {

			clearInput(x, 0, 9);

			setColor(WHITE);
			while (true) {
				print(x, y + 1, "> Continue playing? (");
				print(PINK, "Y");
				print(WHITE, "/");
				print(PINK, "N");
				print(WHITE, ")");
				print(GREEN, "> ");
				strInput = readLimitedInput(x + 27, y + 1);

				if (strInput == "N") {
					return;
				}
				else if (!((strInput == "N") || (strInput == "Y"))) {

					setColor(WHITE);
					print(x + 27, y + 1, " ");
					print(x, y + 2, "Provide a correct option");

				}
				else {

					break;

				}

			} // !Confirmation loop

		}

		// Finding a winner
		if (iHitCounter[iTurn % 2] == 17) {

			break;

		}
		else {

			iTurn++;

		}

	} // !while loop

	// Now that we found a winner, we display it
	getWinner(iTurn % 2);

}

// Generating a random coordinate for the computer
// @param _iTurn for testing purposes, main turn will be 1 (computer)
// @param _iTempRow the temporal row that'll add to the final one
// @param _iTempCol the temporal column that'll add to the final one
// @return void
void Game::setRandomCoordinates(int _iTurn, int _iTempRow, int  _iTempCol) {

	bool canExitLoop = false;
	// for parsing our row as a letter
	char charToString;
	// For knowing how many steps we should take
	int howManySteps = 0;

	if (bHasFoundShip == true) {

		if (iPlayerHitGrid[_iTempRow][_iTempCol] == 1) {

			if (isShipSunkYet(iPlayerGrid[_iTempRow][_iTempCol] - 1, _iTempRow, _iTempCol, 1) == false) {

				while (true) {

					// Vertical
					if (iShipDirection == 1) {

						while (true) {

							// returns true if can hit the position up to where it previously hit
							bool canGoUp = (_iTempCol > 0) && (iPlayerHitGrid[_iTempRow][_iTempCol] == 1) &&
								((iPlayerMissGrid[_iTempRow][_iTempCol - 1] == 0) && (iPlayerHitGrid[_iTempRow][_iTempCol - 1] == 0));

							// returns true if can hit the position down to where it previously hit
							bool canGoDown = (_iTempCol < 9) && (iPlayerHitGrid[_iTempRow][_iTempCol] == 1) &&
								((iPlayerMissGrid[_iTempRow][_iTempCol + 1] == 0) && (iPlayerHitGrid[_iTempRow][_iTempCol + 1] == 0));

							if (canGoUp && !canGoDown) {

								_iTempCol--;
								break;

							}
							else if (!canGoUp && canGoDown) {

								_iTempCol++;
								break;

							}
							else if (canGoUp && canGoDown) {

								if ((rand() % 2) % 2 == 0) {

									_iTempCol--;

								}
								else {

									_iTempCol++;

								}

								break;

							}
							else {

								if (_iTempCol < 9) {

									_iTempCol++;

								}
								else {

									_iTempCol = 0;

								}

							}

						}

					} // !Vertical
					  // Horizontal
					else if (iShipDirection == -1) {

						while (true) {

							// returns true if can hit the position left to where it previously hit
							bool canGoLeft = (_iTempRow > 0) && (iPlayerHitGrid[_iTempRow][_iTempCol] == 1) &&
								((iPlayerMissGrid[_iTempRow - 1][_iTempCol] == 0) && (iPlayerHitGrid[_iTempRow - 1][_iTempCol] == 0));

							// returns true if can hit the position right to where it previously hit
							bool canGoRight = (_iTempRow < 9) && (iPlayerHitGrid[_iTempRow][_iTempCol] == 1) &&
								((iPlayerMissGrid[_iTempRow + 1][_iTempCol] == 0) && (iPlayerHitGrid[_iTempRow + 1][_iTempCol] == 0));

							if (canGoLeft && !canGoRight) {

								_iTempRow--;
								break;

							}
							else if (!canGoLeft && canGoRight) {

								_iTempRow++;
								break;

							}
							else if (canGoLeft && canGoRight) {

								if ((rand() % 2) % 2 == 0) {

									_iTempRow--;

								}
								else {

									_iTempRow++;

								}

								break;

							}
							else {

								if (_iTempRow < 9) {

									_iTempRow++;

								}
								else {

									_iTempRow = 0;

								}

							}

						}

					} // !Horizontal
					  // Direction not yet known
					else {

						findOpenPath(_iTempRow, _iTempCol);

					} // !Direction not yet known

					if ((iPlayerHitGrid[_iTempRow][_iTempCol] == 1) || (iPlayerMissGrid[_iTempRow][_iTempCol] == 1)) {

						// Repeat the process until it finds a direction to hit

					}
					else {

						if ((_iTempRow >= 0 && _iTempCol >= 0) && (_iTempRow <= 9 && _iTempCol <= 9)) {

							break;

						}
						else {

							iShipDirection *= -1;

						}

					}

				} // !While loop

			} // !Ship hasn't been sunk

		} // !Has hit the position

	} // !Has found the ship
	  // Hasn't found a ship
	else {

		while (true) {

			_iTempRow = rand() % 10;
			_iTempCol = rand() % 10;

			if (iPlayerHitGrid[_iTempRow][_iTempCol] == 1) {

				_iTempRow = (rand() % 10) / (rand() % 5 + 1);
				_iTempCol = (rand() % 10) / (rand() % 5 + 1);

			}
			else if (iPlayerMissGrid[_iTempRow][_iTempCol] == 1) {

				findOpenPath(_iTempRow, _iTempCol);

			}
			else {

				break;

			}

		}

	}

	charToString = _iTempRow + 65;
	strInput[0] = charToString;
	iRow = _iTempRow;
	iCol = _iTempCol;

}

// Check for the next open path
// @param _riRow the current row
// @param _riCol the current column
// @return void
void Game::findOpenPath(int& _riRow, int& _riCol) const {

	int hitChance = 0;

	// Left
	if ((iPlayerMissGrid[_riRow - 1][_riCol] == 0) && (iPlayerHitGrid[_riRow - 1][_riCol] == 0)) {

		if (_riRow > 0) {

			hitChance += 1;

		}

	}
	// Down
	if ((iPlayerMissGrid[_riRow][_riCol + 1] == 0) && (iPlayerHitGrid[_riRow][_riCol + 1] == 0)) {

		if (_riCol < 9) {

			hitChance += 3;

		}

	}
	// Right
	if ((iPlayerMissGrid[_riRow + 1][_riCol] == 0) && (iPlayerHitGrid[_riRow + 1][_riCol] == 0)) {

		if (_riRow < 9) {

			hitChance += 5;

		}

	}
	// Up
	if ((iPlayerMissGrid[_riRow][_riCol - 1] == 0) && (iPlayerHitGrid[_riRow][_riCol - 1] == 0)) {

		if (_riCol > 0) {

			hitChance += 7;

		}

	}

	// None
	if (hitChance == 0) {

		if (iPlayerHitGrid[_riRow + 1][_riCol] == 1) {

			_riRow++;

		}
		else if (iPlayerHitGrid[_riRow - 1][_riCol] == 1) {

			_riRow--;

		}
		else if (iPlayerHitGrid[_riRow][_riCol + 1] == 1) {

			_riCol++;

		}
		else if (iPlayerHitGrid[_riRow][_riCol - 1] == 1) {

			_riCol--;

		}

	}
	// Left
	else if (hitChance == 1) {

		_riRow--;

	}
	// Down
	else if (hitChance == 3) {

		_riCol++;

	}
	// Left, Down
	else if (hitChance == 4) {

		if ((rand() % 2) % 2 == 0) {

			_riRow--;

		}
		else {

			_riCol++;

		}

	}
	// Right
	if (hitChance == 5) {

		_riRow++;

	}
	// Left, Right
	else if (hitChance == 6) {

		if ((rand() % 2) % 2 == 0) {

			_riRow--;

		}
		else {

			_riRow++;

		}

	}
	// Up
	else if (hitChance == 7) {

		_riCol--;

	}
	// Left, Up - Right, Down
	else if (hitChance == 8) {

		// Left, Up
		if (((iPlayerMissGrid[_riRow][_riCol - 1] == 0) && (iPlayerHitGrid[_riRow][_riCol - 1] == 0)) && (_riRow > 0 && _riCol > 0)) {

			if ((rand() % 2) % 2 == 0) {

				_riRow--;

			}
			else {

				_riCol--;

			}

		}
		// Right, Down
		else if (((iPlayerMissGrid[_riRow][_riCol + 1] == 0) && (iPlayerHitGrid[_riRow][_riCol + 1] == 0)) && (_riRow < 9 && _riCol < 9)) {

			if ((rand() % 2) % 2 == 0) {

				_riRow++;

			}
			else {

				_riCol++;

			}

		}

	}
	// Left, Down, Right
	else if (hitChance == 9) {

		if ((rand() % 2) % 2 == 0) {

			_riCol++;

		}
		else {

			if ((rand() % 2) % 2 == 0) {

				_riRow--;

			}
			else {

				_riRow++;

			}

		}

	}
	// Down, Up
	else if (hitChance == 10) {

		if ((rand() % 2) % 2 == 0) {

			_riCol++;

		}
		else {

			_riCol--;

		}

	}
	// Left, Down, Up
	else if (hitChance == 11) {

		if ((rand() % 2) % 2 == 0) {

			_riRow--;

		}
		else {

			if ((rand() % 2) % 2 == 0) {

				_riCol++;

			}
			else {

				_riCol--;

			}

		}

	}
	// Right, Up
	else if (hitChance == 12) {

		if ((rand() % 2) % 2 == 0) {

			_riRow++;

		}
		else {

			_riCol--;

		}

	}
	// Left, Right, Up
	else if (hitChance == 13) {

		if ((rand() % 2) % 2 == 0) {

			_riCol--;

		}
		else {

			if ((rand() % 2) % 2 == 0) {

				_riRow--;

			}
			else {

				_riRow++;

			}

		}

	}
	// Down, Right, Up
	else if (hitChance == 15) {

		if ((rand() % 2) % 2 == 0) {

			_riRow++;

		}
		else {

			if ((rand() % 2) % 2 == 0) {

				_riCol++;

			}
			else {

				_riCol--;

			}

		}

	}
	// Left, Down, Right, Up
	else if (hitChance == 16) {

		int iRandom = rand() % 4;

		if (iRandom == 0) {

			_riRow--;

		}
		else if (iRandom == 1) {

			_riCol++;

		}
		else if (iRandom == 2) {

			_riRow++;

		}
		else if (iRandom == 3) {

			_riCol--;

		}

	}

	if (_riRow < 0) {

		_riRow = 0;

	}

	if (_riCol < 0) {

		_riCol = 0;

	}

}

// Checking which player has been hit
// @param _iRow the current row
// @param _iCol the current column
// @param _iTurn the current turn
// @return void
void Game::checkForHit(int _iRow, int _iCol, int _iTurn) {

	/// Player
	if (iTurn % 2 == 0) {

		// Hit
		if (iComputerGrid[_iRow][_iCol] >= 1 && iComputerGrid[_iRow][_iCol] <= 5) {

			iComputerHitGrid[_iRow][_iCol] = 1;
			if (isShipSunkYet(iComputerGrid[_iRow][_iCol] - 1, _iRow, _iCol, iTurn % 2) == true) {

				print(44, 4, RED, "> Sunk opponent's " + SHIP_NAME[iComputerGrid[_iRow][_iCol] - 1]);

			}
			else {

				print(44, 4, RED, "> You hit " + SHIP_NAME[iComputerGrid[_iRow][_iCol] - 1]);

			}

			print(_iRow * 2 + 23, _iCol + 2, RED, getShipCode(iComputerGrid[_iRow][_iCol] - 1));
			IF_DEBUG(1) {
				print(_iRow * 2 + 1, _iCol + 15, RED, getShipCode(iComputerGrid[_iRow][_iCol] - 1));
			}

			iHitCounter[0]++;

		}
		// Miss
		else {

			print(44, 4, PINK, "> You missed your shot!");
			iComputerMissGrid[_iRow][_iCol] = 1;
			print(_iRow * 2 + 23, _iCol + 2, DARKPINK, 'o');

		}

	} // Player
	/// Computer
	else if (iTurn % 2 == 1) {

		// Hit
		if (iPlayerGrid[_iRow][_iCol] >= 1 && iPlayerGrid[_iRow][_iCol] <= 5) {

			iPlayerHitGrid[_iRow][_iCol] = 1;
			bHasFoundShip = true;
			iHitRow = _iRow;
			iHitCol = _iCol;
			iShipDirection = getShipDirection(_iRow, _iCol);
			if (isShipSunkYet(iPlayerGrid[_iRow][_iCol] - 1, _iRow, _iCol, iTurn % 2) == true) {

				bHasFoundShip = false;
				print(44, 4, RED, "> Opponent sunk " + SHIP_NAME[iPlayerGrid[_iRow][_iCol] - 1]);

			}
			else {

				print(44, 4, RED, "> Opponent hits " + SHIP_NAME[iPlayerGrid[_iRow][_iCol] - 1]);

			}

			IF_DEBUG(1) {

				print(_iRow * 2 + 23, _iCol + 15, RED, getShipCode(iPlayerGrid[_iRow][_iCol] - 1));

			}

			print(_iRow * 2 + 1, _iCol + 2, RED, getShipCode(iPlayerGrid[_iRow][_iCol] - 1));
			iHitCounter[1]++;

		}
		// Miss
		else {

			print(44, 4, PINK, "> Your opponent missed!");
			iPlayerMissGrid[_iRow][_iCol] = 1;
			IF_DEBUG(1) {

				print(_iRow * 2 + 23, _iCol + 15, DARKPINK, 'o');

			}

		}

	} // Computer

}

// Direction of the ship
// @param _iRow the current row to check
// @param _iCol the current column to check
// @return void
int Game::getShipDirection(int _iRow, int _iCol) const {

	int direction = 0;

	char currentShipCode = getShipCode(iPlayerGrid[_iRow][_iCol] - 1);
	char upperShipCode = getShipCode(iPlayerGrid[_iRow][_iCol - 1] - 1);
	char lowerShipCode = getShipCode(iPlayerGrid[_iRow][_iCol + 1] - 1);
	char rightShipCode = getShipCode(iPlayerGrid[_iRow + 1][_iCol] - 1);
	char leftShipCode = getShipCode(iPlayerGrid[_iRow - 1][_iCol] - 1);

	// Vertical and horizontall
	if (((iPlayerHitGrid[_iRow][_iCol - 1] == 1) && (_iCol > 0)) || ((iPlayerHitGrid[_iRow][_iCol + 1] == 1) && (_iCol < 9)) ||
		((iPlayerHitGrid[_iRow - 1][_iCol] == 1) && (_iRow > 0)) || ((iPlayerHitGrid[_iRow + 1][_iCol] == 1) && (_iRow < 9))) {

		if ((_iCol == 0) && (currentShipCode == lowerShipCode)) {

			direction = 1;

		}
		else if ((_iCol > 0) && (currentShipCode == upperShipCode || currentShipCode == lowerShipCode)) {

			direction = 1;

		}
		else if ((_iRow == 0) && (currentShipCode == rightShipCode)) {

			direction = -1;

		}
		else if ((_iRow > 0) && (currentShipCode == rightShipCode || currentShipCode == leftShipCode)) {

			direction = -1;

		}
		else {

			direction = 0;

		}

	}
	// No direction found
	else {

		direction = 0;

	}

	return direction;

}

// Checking for which ship has been sunk by comparing the ship's hit counter with the ship's size
// @param _iShipCode the code of the ship that has been hit
// @param _iRow the current row that has been hit
// @param _iCol the current column that has been hit
// @param _iTurn the current turn
// @return boolean
bool Game::isShipSunkYet(int _iShipCode, int _iRow, int _iCol, int _iTurn) {

	shipHitCounter = 0;

	for (int i = 0; i < 10; ++i) {

		for (int j = 0; j < 10; ++j) {

			// Player
			if (_iTurn % 2 == 0) {

				if ((iComputerGrid[i][j] == _iShipCode + 1) && (iComputerHitGrid[i][j] == 1)) {

					shipHitCounter++;

				}

			}
			// Computer
			else {

				if ((iPlayerGrid[i][j] == _iShipCode + 1) && (iPlayerHitGrid[i][j] == 1)) {

					shipHitCounter++;

				}

			}

		}

	}

	// If the hit counter has the same length as the ship's size, all the positions have been hit
	// thus sinking the ship
	if (shipHitCounter == getShipSize(_iShipCode)) {

		return true;

	}
	else {

		return false;

	}

}

// Display winner and message
// @param _iPlayer the current player to check
// @return void
void Game::getWinner(int _iPlayer) const {

	clearInput(44, 0, 24);
	if (_iPlayer == 0) {

		print(44, 1, YELLOW, "> YOU WIN!");

	}
	else {

		print(44, 1, YELLOW, "> COMPUTER WINS!");

	}
	gotoxy(44, 11, true);
	confirmRETURN(44, 3);

}

// Drawing ship information
// @param _iX the 'x' coordinate to print at
// @param _iY the 'y' coordinate to print at
// @return void
void Game::drawShipInfo(int _iX, int _iY) const {

	print(_iX + 10, _iY + 18, GREEN, "SHIP INFORMATION");
	// Ship info
	for (int i = 0; i < 5; ++i) {

		print(_iX + 2, _iY + 19 + i, SHIP_NAME[i] + "- (");
		print(RED, getShipCode(i));
		print(WHITE, ") - Size ");
		print(RED, to_string(getShipSize(i)));

	}
	// Borders
	for (int i = _iX; i < 79; ++i) {

		for (int j = 0; j <= 7; ++j) {

			if ((i == _iX || i == 78) && (j > 0 && j < 7)) {

				print(i, _iY + 17 + j, "|");

			}
			if ((j == 0 || j == 7) && (i > 0 && i < 79)) {

				print(i, _iY + 17 + j, "=");

			}

		}

	}

}

/**************************************/
/*                                    */
/*             GAME OVER              */
/*                                    */
/**************************************/

// Drawing the game over screen
// @return void
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
	print(x, y, "> PLAY AGAIN?");
	print(x, ++y, "");
	print(PINK, "Y");
	print(WHITE, "(yes)/ ");
	print(PINK, "N");
	print(WHITE, "(no)");
	print(x, ++y, "Type your option and press ");
	print(GREEN, "ENTER / RETURN");
	print(x, ++y, "Option");
	print(GREEN, "> ");

}

// Asks if player wants to keep playing
// @return std::string
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
// @return void
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
// @return void
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
// @return void
void Game::drawScreenBorders() {

	setColor(GREEN);
	for (int i = 0; i < 80; ++i) {

		for (int j = 0; j <= 24; ++j) {

			// Vertical borders
			if ((j == 0 || j == 24)) {
				print(i, j, "#");
			}
			// Horizontal borders
			if ((i == 0 || i == 77) && (j > 0 && j < 24)) {
				print(i, j, "[x]");
			}

		}

	}

	gotoxy(0, 0, true);

}