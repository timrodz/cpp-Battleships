//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2005 - 2015 Media Design School
// 
// File name   : main.cpp
// Description : This file contains the main loop with all the game's states
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

	Game game;
	GameState gameState;

	enum eState {
		MENU = 0,
		SETUP = 1,
		GAME = 2,
		GAMEOVER = 3,
		QUIT = 4,
		CREDITS = 5
	};
	
	// Options for each menu
	int iMenuOption = 0;
	int iSortOption = 0;
	//int winner = -1;
	char cGameOverOption = '\0';

	// Initial state
	gameState.setSortMode(MENU);
	
	while (true) {

		// Menu
		while (gameState.getSortMode() == MENU) {

			gameState.drawState(MENU);
			iMenuOption = game.setMenu();

			if (iMenuOption == 1) {
				gameState.setSortMode(SETUP);
			}
			else if (iMenuOption == 2) {
				gameState.setSortMode(CREDITS);
			}
			else if (iMenuOption == 3) {
				gameState.setSortMode(GAMEOVER);
			}

		} // Menu

		// Setup
		while (gameState.getSortMode() == SETUP) {

			gameState.drawState(SETUP);

			iSortOption = game.setSetupMode();

			if (iSortOption == 1) {
				game.sortAutomatic();
				gameState.setSortMode(GAME);
			}
			else if (iSortOption == 2) {
				game.sortManual();
				gameState.setSortMode(GAME);
			}
			else if (iSortOption == 0) {
				gameState.setSortMode(MENU);
			}

			if (game.getSortMode() == "X") {
				gameState.setSortMode(SETUP);
			}

		} // !Setup
		
		// Game
		while (gameState.getSortMode() == GAME) {

			gameState.drawState(GAME);

			game.updateGame();

			if (game.getSortMode() == "X") {
				gameState.setSortMode(SETUP);
			}
			else {
				gameState.setSortMode(GAMEOVER);
			}

		} // !Game

		// Game over
		while (gameState.getSortMode() == GAMEOVER) {

			gameState.drawState(GAMEOVER);
			cGameOverOption = game.setGameOver().at(0);

			if (cGameOverOption == 'Y') {
				gameState.setSortMode(MENU);
			}
			else if (cGameOverOption == 'N') {
				gameState.setSortMode(QUIT);
			}			

		} // !Game over

		// Credits
		while (gameState.getSortMode() == CREDITS) {
			gameState.drawState(CREDITS);
			gameState.setSortMode(MENU);
		} // !Credits 

		// Quit
		if (gameState.getSortMode() == QUIT) {
			gameState.drawState(QUIT);
			break;
		} // !Quit

	} // !Main loop
	
	game.~Game();
	return 0;

}