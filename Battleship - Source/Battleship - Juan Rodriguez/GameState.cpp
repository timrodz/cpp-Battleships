//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2005 - 2015 Media Design School
// 
// File name   : GameState.cpp
// Description : Game state manager
// Author      : Juan Rodriguez
// Mail        : juan.rod6618@mediadesignschool.com
// 

#include "GameState.h"

// Drawing the state's correspondant screen
void GameState::drawState(int state) {
	if (state == MENU) {
		game.drawMenuScreen();
	}
	else if (state == SETUP) {
		game.drawSetupScreen();
	}
	else if (state == GAME) {
		game.drawGameScreen();
	}
	else if (state == GAMEOVER) {
		game.drawGameOverScreen();
	}
	else if (state == QUIT) {
		game.drawQuitScreen();
	}
	else if (state == CREDITS) {
		game.drawCreditsScreen();
	}
}

// Setting the state
void GameState::setState(int state) {
	currentState = state;
}

// Getting the current state
int GameState::getState() const {
	return currentState;
}