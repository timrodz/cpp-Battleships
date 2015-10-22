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

// Library includes
#include <iostream>
#include <string>
#include <windows.h>

// Local includes
#include "Game.h"
#include "GameState.h"

int main() {

	int sortOption = 0;

	enum State {
		MENU     = 0,
		SETUP    = 1,
		GAME     = 2,
		GAMEOVER = 3,
		QUIT     = 4
	};
	
	Game game;

	GameState gs;

	//game.setGrid();
	//game.setAvailableShips();
	gs.setState(MENU);
	
	while (true) {
		
		//gs.setState(QUIT);

		// TODO
		while (gs.getState() == MENU) {

			gs.drawState(MENU);

			gs.setState(SETUP);

		} /// Menu

		while (gs.getState() == SETUP) {

			gs.drawState(SETUP);
			//gs.drawState(GAME);
			/*gs.setState(GAME);
			break;*/

			sortOption = game.setupSortMode();

			if (sortOption == 1) {
				game.sortAuto();
				gs.setState(GAME);
			}
			else if (sortOption == 2) {
				game.sortManual();
				gs.setState(GAME);
			}
			else {
				gs.setState(SETUP);
			}

			if (game.getCancelSort() == "CANCEL") {
				gs.setState(SETUP);
			}

		} /// Setup
		
		// TODO
		while (gs.getState() == GAME) {

			gs.drawState(GAME);

			//gs.setState(GAMEOVER);

		} /// Game

		while (gs.getState() == GAMEOVER) {

			gs.drawState(GAMEOVER);
			

			gs.setState(QUIT);

		} /// Game over

		if (gs.getState() == QUIT) {
			gs.drawState(QUIT);
			break;
		}

	} /// Main loop
	
	game.~Game();
	return 0;
}