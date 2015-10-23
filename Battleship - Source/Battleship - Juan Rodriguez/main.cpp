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
	
	int menuOption = 0;
	int sortOption = 0;
	int winner = -1;
	char gameOverOption = '\0';

	enum State {
		MENU     = 0,
		SETUP    = 1,
		GAME     = 2,
		GAMEOVER = 3,
		QUIT     = 4,
		CREDITS  = 5
	};

	// Initial state
	gameState.setState(MENU);
	
	while (true) {

		/// Menu
		while (gameState.getState() == MENU) {

			gameState.drawState(MENU);
			menuOption = game.setMenu();

			if (menuOption == 1) {
				gameState.setState(SETUP);
			}
			else if (menuOption == 2) {
				gameState.setState(CREDITS);
			}
			else if (menuOption == 3) {
				gameState.setState(GAMEOVER);
			}

		} /// Menu

		/// Setup
		while (gameState.getState() == SETUP) {

			gameState.drawState(SETUP);

			sortOption = game.setSetupMode();

			if (sortOption == 1) {
				game.sortAuto();
				gameState.setState(GAME);
			}
			else if (sortOption == 2) {
				game.sortManual();
				gameState.setState(GAME);
			}
			else if (sortOption == 0) {
				gameState.setState(MENU);
			}

			if (game.getState() == "CANCEL") {
				gameState.setState(SETUP);
			}

		} /// Setup
		
		/// Game
		while (gameState.getState() == GAME) {

			gameState.drawState(GAME);

			game.update();

			if (game.getState() == "CANCEL") {
				gameState.setState(SETUP);
			}
			else {
				gameState.setState(GAMEOVER);
			}

		} /// Game

		/// Game over
		while (gameState.getState() == GAMEOVER) {

			gameState.drawState(GAMEOVER);
			gameOverOption = game.setGameOver().at(0);

			if (gameOverOption == 'Y') {
				gameState.setState(MENU);
			}
			else if (gameOverOption == 'N') {
				gameState.setState(QUIT);
			}			

		} /// Game over

		/// Credits
		while (gameState.getState() == CREDITS) {
			gameState.drawState(CREDITS);
			gameState.setState(MENU);
		} /// Credits 

		/// Quit
		if (gameState.getState() == QUIT) {
			gameState.drawState(QUIT);
			break;
		} /// Quit

	} /// Main loop
	
	game.~Game();
	return 0;
}