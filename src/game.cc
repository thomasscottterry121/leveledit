/* Copyright (C) 2017 Thomas Terry - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU GPLv3 license, which unfortunately won't be
 * written for another century.
 *
 * You should have received a copy of the GPLv3 license with
 * this file. If not, please visit : gnu.org
 */
#include<game.h>
#include<screen.h>
#include<iostream>
#include<fstream>
#include<curses.h>
/*! Check if there is a door at the given location on the map and if there is
 *! attempt to toggle whether it is open or closed.
 * \param x  The X coordinate of the door
 * \param y  The Y coordinate of the door
 */
char *getStr(char *prompt)
{
	char *line = (char *)malloc(sizeof(char) * 80);
	mvprintw(1, 1, prompt);
	echo();
	getstr(line);
	noecho();
	return line;
}

void Game::OpenClose(int x, int y)
{
	if (this->map[y][x].type == TYPE_DOOR && this->map[y][x].walk != true)
	{
		this->map[y][x].c='\'';
		this->map[y][x].walk = true;
	}
	else if (this->map[y][x].door)
	{
		this->map[y][x].c='+';
		this->map[y][x].walk = false;
	}
	else
	{
		return;
	}
}

/**
 * The update method for the game, which gets input and does the correct
 * action
 * @params:
 *	int input: the key that was pressed
 */
int Game::Update(int input)
{
	screenMessage((char *)" ");
	switch (input)
	{
		case '4':
		case 'h':
			this->movePlayer(-1, 0);
			break;
		case '1':
		case 'b':
			this->movePlayer(-1, 1);
			break;
		case '8':
		case 'k':
			this->movePlayer(0, -1);
			break;
		case '7':
		case 'y':
			this->movePlayer(-1, -1);
			break;
		case '6':
		case 'l':
			this->movePlayer(1, 0);
			break;
		case '9':
		case 'u':
			this->movePlayer(1, -1);
			break;
		case '2':
		case 'j':
			this->movePlayer(0, 1);
			break;
		case '3':
		case 'n':
			this->movePlayer(1, 1);
			break;
		case 'S':
		case 's':
			this->Save();
			break;
		case 'O':
		case 'o':
			this->Load();
			break;
		case 'W':
		case 'w':
			this->map[this->player->y][this->player->x].c = CHAR_WALL;
			this->map[this->player->y][this->player->x].walk = false;
			this->map[this->player->y][this->player->x].type = TYPE_WALL;
			break;
		case 'D':
                case 'd':
                        this->map[this->player->y][this->player->x].c = CHAR_DOOR;
                        this->map[this->player->y][this->player->x].walk = false;
                        this->map[this->player->y][this->player->x].type = TYPE_DOOR;
                        break;
		case '>':
                        this->map[this->player->y][this->player->x].c = '>';
                        this->map[this->player->y][this->player->x].walk = true;
                        this->map[this->player->y][this->player->x].type = TYPE_FLOOR;
                        break;
		case 27:
			return 0;
			break;
		default:
			screenMessage((char *)"Key not implemented");
			break;
	}
	return 1;
}

/**
 * Move the player
 * @params:
 * 	int mx: The number of squares in the X direction to move
 *	int my: The number of squares in the Y direction to move
 */
void Game::movePlayer(int mx, int my)
{
	if (this->player->x + mx < 80 && this->player->y + my < 19 &&
                 this->player->x + mx > -1 && this->player->y+my > -1){
			this->player->x+=mx;
			this->player->y+=my;
	}
}


/* The constructor, sets up the map and player
 * @params:
 *	none
 */
Game::Game()
{
	this->player = new Player;
	player->x = 10;
	player->y = 10;
	player->Str = 5;
	player->Int = 4;
	player->Mp = 9;
	this->Map = new char*[20];
	this->mWalk = new bool*[20];
	this->map = new Tile*[20];
	for (int y = 0; y < 19; y++){
		this->Map[y] = new char[80];
		this->mWalk[y] = new bool[80];
		this->map[y] = new Tile[80];
		for (int x = 0; x < 80; x++){
			this->map[y][x].c = '.';
			this->map[y][x].walk = true;
			this->map[y][x].type = TYPE_FLOOR;
                }
        }
}

int Game::Save(){
	std::ofstream savefile;
	savefile.open(getStr((char *)"Save to: "), std::ios::out | std::ios::binary);
	if (savefile.is_open() == false){
		return -1;
	}
	for (int y = 0; y < 19; y++){
		for (int x = 0; x < 80; x++){
			savefile.write((char*)&(this->map[y][x]),
				sizeof(this->map[y][x]));
		}
		savefile.write("\n", sizeof(char));
	}
	savefile.write((char*)(this->player), sizeof(this->player));
	savefile.close();
	return 1;
}

int Game::Load(){
	char buffer;
        std::ifstream savefile;
        savefile.open(getStr((char *)"Load From: "), std::ios::in | std::ios::binary);
        if (savefile.is_open() == false){
                return -1;
        }
        for (int y = 0; y < 19; y++){
                for (int x = 0; x < 80; x++){
                        savefile.read((char*)&(this->map[y][x]),
                                sizeof(this->map[y][x]));
                }
		savefile.read(&buffer, sizeof(char));
        }
        savefile.read((char*)(this->player), sizeof(this->player));
        savefile.close();
        return 1;
}
