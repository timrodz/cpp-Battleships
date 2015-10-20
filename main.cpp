//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2005 - 2015 Media Design School
// 
// File name   : main.cpp
// Description : This file contains our main code (most of the work is done via Game.cpp
// Author      : Juan Rodriguez
// Mail        : juan.rod6618@mediadesignschool.com
// 

// Library headers
#include <iostream>
#include <string>
#include <windows.h>

// Local headers
#include "Game.h"
//#include "Screen.h"
////#include "Ship.h"

int main() {
	int choice = 0;

	Game game;
	game.setFirstRunValue(true);
	game.setGrid(10, 10);
	game.setAvailableShips(5);
	game.drawBattleScreen();
	if (game.getFirstRunValue() == true) {
		choice = game.setupSortMode();
		game.setFirstRunValue(false);
		if (choice == 1) {
			game.automaticSort();
		}
		else {
			game.manualSort();
		}
	}
	
	std::cin.get();
	return 0;
}