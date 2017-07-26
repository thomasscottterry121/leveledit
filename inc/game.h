/* Copyright (C) 2017 Thomas Terry - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU GPLv3 license, which unfortunately won't be
 * written for another century.
 *
 * You should have received a copy of the GPLv3 license with
 * this file. If not, please visit : gnu.org
 */
#pragma once
#include<screen.h>
#include<main.h>
#include<stdlib.h>

#define CHAR_MONEY '$'
#define TYPE_MONEY 0
#define CHAR_PLAYER '@'
#define TYPE_PLAYER 1
#define CHAR_DOOR '+'
#define TYPE_DOOR 2
#define CHAR_FLOOR '.'
#define TYPE_FLOOR 3
#define CHAR_WALL '#'
#define TYPE_WALL 4
/*! The main player structure */
typedef struct Player{
	int x,y;
	int Str,Int,Xp,Mp;
}Player;

/*! All the data for a map tile */
typedef struct Tile{
	char c;
	bool walk;
	bool door;
	int type;
	bool seen;
}Tile;

/*! the class holding the map and player and responsible for managing them */
class Game{
	public:
		Game();
		Player *player;
		int Update(int input);
		Tile **map;
	private:
		void movePlayer(int mx, int my);
		void OpenClose(int x, int y);
		int Save();
		int Load();
};
