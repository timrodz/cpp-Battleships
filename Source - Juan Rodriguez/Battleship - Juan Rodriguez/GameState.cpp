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
void GameState::drawState(int _iState) {

	if (_iState == MENU) {

		game.drawMenuScreen();

	}
	else if (_iState == SETUP) {

		game.drawSetupScreen();

	}
	else if (_iState == GAME) {

		game.drawGameScreen();

	}
	else if (_iState == GAMEOVER) {

		game.drawGameOverScreen();

	}
	else if (_iState == QUIT) {

		game.drawQuitScreen();

	}
	else if (_iState == CREDITS) {

		game.drawCreditsScreen();

	}

}

// Setting the state
void GameState::setSortMode(int _iState) {

	iCurrentState = _iState;

}

// Getting the current state
int GameState::getSortMode() const {

	return iCurrentState;

}