//#include <iostream>
//#include <cassert>

#include "GameState.h"

GameState::GameState() {

}


GameState::~GameState() {

}

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
}

void GameState::setState(int state) {
	currentState = state;
}

int GameState::getState() const {
	return currentState;
}