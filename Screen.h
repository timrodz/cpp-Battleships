//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// 
// (c) 2005 - 2015 Media Design School
// 
// File name   : Screen.h
// Description : Drawing of the screen, movement and determining ship position
// Author      : Juan Rodriguez
// Mail        : juan.rod6618@mediadesignschool.com
// 

#pragma once
#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <windows.h>

// Drawing the screen's borders
void drawBattleScreen();
// Drawing the ships in the screen
void drawShips();
// Going to a desired position in the screen
// SCREEN DIMENSIONS: 80 wide by 24 tall
void gotoxy(int x, int y);

#endif /* Screen.h */