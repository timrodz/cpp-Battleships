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
#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>

// Local includes
#include "Screen.h"

class Game {
public:

	Game();
	~Game();

	/// GAME START ///
	// Setup of our 12x12 grid (extra spaces for collision checking)
	void setCollisionGrid();

	// Resets the ships
	void setAvailableShips();

	// Get number of ships
	int getPlacedShips(int) const;

	// This method checks if either the player and the AI can place ships
	bool canPlaceShips(int _iCode) const;

	// Getting the size of the ships
	int getShipSize(int _iCode) const;

	// Getting the code (character that represents) for the current ship
	char getShipCode(int _iCode) const;

	/// Navigation ///
	void setSortMode(std::string _strSortMode);
	std::string getSortMode() const;

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
	void printAvailableShips() const;

	// Automatically sorting the grid
	void sortAutomatic();

	// Manually sorting the grid
	void sortManual();

	/// Only can be accessed through our sortAuto and sortManual methods
private:

	// This will only be called inside the setup
	void setShipAuto(int _iPlayer);
	void setShipManual();

	/// Rest of the public functions
public:

	// Gets our coordinates (row, column, direction)
	// It'll only get direction and confirmation for placement if the player's on manual setup
	void setFireCoordinates(std::string& _rStrInput, int& _riRow, int& _riCol, int _iX, int _iY);

	// This method checks for collisions and available spaces
	// FEATURES:
	// -> Knows which direction to place the ship
	// -> Knows if it's the player's or computer's turn
	// -> Places ships on the screen accordingly and sets the ship unavailable after it's been used
	void createShip(int _iDir, int _iRow, int _iCol, int _iShipID, int _iPlayer);

	/// GAME ///
	// Drawing the state
	void drawGameScreen();

	// Game loop
	void updateGame();

	// Checking if a ship has been left behind while hitting
	void checkForMissingShips();

	// Creating a random coordinate (for the enemy)
	void setRandomCoordinates(int _iCurrentTurn, int _iTempRow, int  _iTempCol);

	// Finding the next open path
	void findOpenPath(int& _riRow, int& _riCol) const;

	// Checking collision
	void checkForHit(int _iRow, int _iCol, int _iTurn);

	// Direction of the ship
	int getShipDirection(int _iRow, int _iCol) const;

	// Knowing if the ship has been sunk or not
	bool isShipSunkYet(int _iShipCode, int _iRow, int _iCol, int _iTurn);

	// When a winner is found
	void getWinner(int _iPlayer) const;

	// Drawing ship information
	void drawShipInfo(int _iX, int _iY) const;

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
	void drawScreenBorders() const;

	/// Private members
private:
	// Keeping track of our turns
	int iTurn;

	// To make sure we can only set up a maximum of 5 ships (Per player)
	static const int MAX_SHIPS;

	// Reading the ship to place
	std::string strInput;
	int iShipModel;;

	// SETUP
	int iSetupMode;
	int iRow, iCol;
	char cLetter;
	char cDir;

	// GAME
	std::string strContinuePlaying;
	// Determining how many hits has our ship received
	int shipHitCounter;
	bool bHasFoundShip;
	int iShipDirection;
	int shipsLeft[2];
	int iHitRow;
	int iHitCol;

	// GAME OVER
	std::string confirmExit;

	// Number of ships currently used 
	// (stores up to whatever value *setAvailableShip* takes as parameter)
	int iCurrentShipsPlaced[2];

	// To check whether or not the player has canceled the ship placement
	std::string strCancelSort;

	// Check whether or not we've a free space
	bool bSpaceTaken;

	// our 2D grid
	// We use sizes of 12 because we also need to check if the ship goes out of bounds
	// And our grid gets *imaginarily* drawn from the starting point (1, 1) until (13, 13)
	int iPlayerGrid[12][12];
	int iComputerGrid[12][12];

	// hit/miss grid for the player
	int iPlayerHitGrid[10][10];
	int iPlayerMissGrid[10][10];

	// hit/miss for the computer
	int iComputerHitGrid[10][10];
	int iComputerMissGrid[10][10];

	// Determining who has won
	int iHitCounter[2];

	// playerShips and computerShips will store the used ships
	int* piCurrentPlayerShip;
	int* piCurrentComputerShip;

	// shipAvailable prints the available ships (to place) according to
	// playerShips and computerShips
	static const std::string SHIP_NAME[5];

};

#endif /* Game.h */