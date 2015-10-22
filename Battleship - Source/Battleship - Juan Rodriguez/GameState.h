//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2005 - 2015 Media Design School
// 
// File name   : GameState.h
// Description : This class contains the code for the states of the game
// Author      : Juan Rodriguez
// Mail        : juan.rod6618@mediadesignschool.com
// 

#pragma once
#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include "Game.h"

class GameState {
/// Public methods
public:
	GameState();
	~GameState();

	// For drawing each state according to the game
	void GameState::drawState(int state);
	// Setting our states
	void setState(int state);
	// Getting our states
	int  getState() const;

/// Private member variables
private:

	enum State {
		MENU     = 0,
		SETUP    = 1,
		GAME     = 2,
		GAMEOVER = 3,
		QUIT     = 4
	};

	int currentState;

	// Accessing our game
	Game game;

};

#endif /* GameState.h */