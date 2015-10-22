//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2005 - 2015 Media Design School
// 
// File name   : Ship.cpp
// Description : This class contains the code for our ship
// Author      : Juan Rodriguez
// Mail        : juan.rod6618@mediadesignschool.com
// 

//Library includes
#include <iostream>

//Local includes
#include "Ship.h"
#include "Game.h"
#include "Screen.h"

Ship::Ship() {
	shipCounter = new int[10];
}

Ship::Ship(int ID, int x, int y):shipModel(ID), xPosition(x), yPosition(y) {



}

Ship::~Ship() { delete[] shipCounter; }