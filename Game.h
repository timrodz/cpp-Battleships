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

class Game {
public:
	Game();
	~Game();

	// This method displays the game action
	void drawBattleScreen();
	// This method displays the taken positions
	void drawPositionScreen();

	// Setting up a grid of as many elements as desired (just for fun),
	// although the game requires a 10x10 grid
	// @param rMax the number of rows
	// @param cMax the number of columns
	void setGrid();

	// Automatic or manual setup of the ships
	int setupSortMode();

	// set the value of firstRun
	void setFirstRunValue(bool firstRunValue);

	// get the value of setup
	bool getFirstRunValue() const;

	// Set available ships to use
	void setAvailableShips();
	
	// Get the current available ships
	void printAvailableShips();

	// Get number of ships
	int getDeployedShips(int) const;

	// Automatically sorting the grid
	void automaticSort();
	
	// Manually sorting the grid
	void manualSort();

	// Managing to go to a certain position given x and y coordinates
	//void gotoxy(int, int);

	// Getting the size of the ships
	int getShipSize(int shipType) const;

	// Getting the code (character that represents) for the current ship
	char getShipCode(int code) const;

	// This method checks if either the player and the AI can place ships
	bool canPlaceShips(int i) const;
	
	bool getCancelSort() const;

	/// Private member functions
private:
	void createShipAuto();
	void createShipManual();
	void computerSort();

	/// Member variables
private:
	// To make sure we can only set up a maximum of 5 ships (Per player)
	static const int MAX_SHIPS;

	// Reading the ship to place
	std::string strShip;
	int shipModel;

	// Number of ships currently used 
	// (stores up to whatever value *setAvailableShip* takes as parameter)
	int availableShips[2];
	
	// Check whether or not it's the first run of the game (decided by the constructor)
	bool firstRun;

	// To check whether or not the player has canceled the ship placement
	bool cancelSort;

	// Check whether or not we've a free space
	bool spaceTaken;

	// our 2D grid
	// We use sizes of 12 because we also need to check if the ship goes out of bounds
	// And our grid gets *imaginarily* drawn from the starting point (1, 1) until (13, 13)
	int grid[12][12];
	
	// playerShips and computerShips will store the used ships
	int* playerShips;
	int* computerShips;
	
	// shipAvailable prints the available ships (to place) according to
	// playerShips and computerShips
	static const std::string availableShipsName[5];
};

#endif /* Game.h */