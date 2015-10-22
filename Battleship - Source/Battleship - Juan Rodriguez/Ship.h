//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2005 - 2015 Media Design School
// 
// File name   : Ship.h
// Description : This class contains our ships that'll be drawn in the screen
// Author      : Juan Rodriguez
// Mail        : juan.rod6618@mediadesignschool.com
// 

#pragma once
#ifndef __SHIP_H__
#define __SHIP_H__

class Ship {
private:
	// idShip will store the ID's of our ships
	// These will be used when the player decides to place a ship
	enum shipID {
		AircraftCarrier = 1,
		Battleship = 2,
		Destroyer = 3,
		Submarine = 4,
		PatrolBoat = 5
	};

public:
	// We'll create a ship with the given ID (1-5)
	Ship();
	Ship(int ID, int x, int y);
	~Ship();
private:
	//int ship
	int* shipCounter;
	int shipModel;
	int xPosition;
	int yPosition;
};

#endif /* ship.h */