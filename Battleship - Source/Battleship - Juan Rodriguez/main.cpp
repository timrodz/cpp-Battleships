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
	game.setGrid();
	game.setAvailableShips();
	
	while (game.getFirstRunValue() == true) {

		game.drawBattleScreen();
		choice = game.setupSortMode();
		game.setFirstRunValue(false);

		if (choice == 1) {
			game.sortAuto();
		}
		else if (choice == 2) {
			game.sortManual();
		}
		else {
			game.setFirstRunValue(true);
		}

		if (game.getCancelSort() == "CANCEL") {
			game.setFirstRunValue(true);
		}
		
		// Finished placing ships
		
	}
	
	std::cin.get();
	return 0;
}