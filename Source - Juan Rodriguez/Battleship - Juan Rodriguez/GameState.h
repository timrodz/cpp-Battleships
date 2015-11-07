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
public:
	// Draws according to the current state
	void drawState(int _iState);
	// Sets the current state
	void setSortMode(int _iState);
	// Gets the current state
	int getSortMode() const;

private:
	// Our states
	enum eState {
		MENU = 0,
		SETUP = 1,
		GAME = 2,
		GAMEOVER = 3,
		QUIT = 4,
		CREDITS = 5
	};

	// the current state
	int iCurrentState;

	// Instace of the game for drawing the current state
	Game game;
};




#endif /* GameState.h */