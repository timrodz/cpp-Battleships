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

	// Draws according to the current state
	void GameState::drawState(int state);
	// Sets the current state
	void setState(int state);
	// Gets the current state
	int getState() const;

/// Private member variables
private:

	enum State {
		MENU     = 0,
		SETUP    = 1,
		GAME     = 2,
		GAMEOVER = 3,
		QUIT     = 4,
		CREDITS  = 5
	};

	int currentState;

	// Accessing our game
	Game game;

};

#endif /* GameState.h */