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

#pragma once
#ifndef __GAME_H__
#define __GAME_H__

// Library includes
#include <string>

// Local includes
#include "Screen.h"

class Game {
public:
	Game();
	~Game();

	/// game start ///
	// Setup of our 12x12 grid (extra spaces for collision checking)
	void setCollisionGrid();

	// Resets the ships
	void setAvailableShips();
	
	// Get number of ships
	int getPlacedShips(int) const;
	
	// This method checks if either the player and the AI can place ships
	bool canPlaceShips(int i) const;

	// Getting the size of the ships
	int getShipSize(int shipType) const;
	
	// Getting the code (character that represents) for the current ship
	char getShipCode(int code) const;

	/// Navigation ///
	void setState(std::string setState);
	std::string getState() const;

	/// MENU ///
	// Drawing the state
	void drawMenuScreen();

	// Set menu
	int setMenu();

	/// SETUP ///
	// Drawing the state
	void drawSetupScreen();
	
	// Automatic or manual setup of the ships
	int setSetupMode();
	
	// Get setup mode
	int getSetupMode() const;

	// Get the current available ships
	void printAvailableShips();

	// Automatically sorting the grid
	void sortAuto();

	// Manually sorting the grid
	void sortManual();

/// Only can be accessed through our sortAuto and sortManual methods
private:
	// This will only be called inside the setup
	void createShipAuto(int player);
	void createShipManual();

/// Rest of the public functions
public:
	// Gets our coordinates (row, column, direction)
	// It'll only get direction and confirmation for placement if the player's on manual setup
	void getCoordinate(std::string& inputRow, std::string& inputCol, int& row, int& col, int x, int y);

	// This method checks for collisions and available spaces
	// FEATURES:
	// -> Knows which direction to place the ship
	// -> Knows if it's the player's or computer's turn
	// -> Places ships on the screen accordingly and sets the ship unavailable after it's been used
	void drawShip(int dir, int row, int col, int SHIP_ID, int player);

	/// GAME ///
	// Drawing the state
	void drawGameScreen();

	// Game loop
	void update();

	// Creating a random coordinate (for the enemy)
	void randomCoordinate(int currentTurn, int row, int col, int x, int y);

	// Checking collision
	void checkHit(int row, int col, int currentTurn);

	// Direction of the ship
	int getShipDirection(int row, int col);

	// Knowing if the ship has been sunk or not
	bool hasBeenSunk(int shipCode, int row, int col, int turn);

	// When a winner is found
	void getWinner(int currentPlayer);

	// Drawing ship information
	void drawShipInfo(int x, int y);

	/// GAMEOVER ///
	// Drawing the state
	void drawGameOverScreen();
	std::string setGameOver();

	/// QUIT ///
	// Drawing the state
	void drawQuitScreen();

	/// CREDITS ///
	// Drawing the state
	void drawCreditsScreen();

	/// Borders of the screen
	void drawScreenBorders();

	/// Private members
private:
	// Keeping track of our turns
	int turn;

	// To make sure we can only set up a maximum of 5 ships (Per player)
	static const int MAX_SHIPS;

	// Reading the ship to place
	std::string inputRow;
	std::string inputShip;
	int shipModel;

	// MENU
	int menuOption;

	// SETUP
	std::string inputSort, inputCol;
	std::string inputDir, confirmPlacement;
	int setupMode;
	int row, col;
	char dir;

	// GAME
	std::string continuePlaying;
	// Determining how many hits has our ship received
	int shipHitCounter;
	bool hasFoundShip;
	int shipDirection;
	int shipsLeft[2];
	int hitRow;
	int hitCol;

	// GAME OVER
	std::string confirmExit;

	// Number of ships currently used 
	// (stores up to whatever value *setAvailableShip* takes as parameter)
	int currentShipsPlaced[2];

	// To check whether or not the player has canceled the ship placement
	std::string cancelSort;

	// Check whether or not we've a free space
	bool spaceTaken;

	// our 2D grid
	// We use sizes of 12 because we also need to check if the ship goes out of bounds
	// And our grid gets *imaginarily* drawn from the starting point (1, 1) until (13, 13)
	int playerGrid[12][12];
	int computerGrid[12][12];

	// hit/miss grid for the player
	int playerHitGrid[10][10];
	int playerMissGrid[10][10];

	// hit/miss for the computer
	int computerHitGrid[10][10];
	int computerMissGrid[10][10];

	// Determining who has won
	int hitCounter[2];
	
	// playerShips and computerShips will store the used ships
	int* currentPlayerShip;
	int* currentComputerShip;
	
	// shipAvailable prints the available ships (to place) according to
	// playerShips and computerShips
	static const std::string SHIP_NAME[5];
};

#endif /* Game.h */