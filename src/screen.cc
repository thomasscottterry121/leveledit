/* Copyright (C) 2017 Thomas Terry - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU GPLv3 license, which unfortunately won't be
 * written for another century.
 *
 * You should have received a copy of the GPLv3 license with
 * this file. If not, please visit : gnu.org
 */
#include<screen.h>

Screen::Screen()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);

	this->message = newwin(2, 80, 0, 0);
	this->map = newwin(19, 80, 2, 0);
	this->stat = newwin(3, 80, 21, 0);
	wclear(stdscr);
	wrefresh(stdscr);
	wclear(this->message);
	wclear(this->stat);
	wclear(this->map);
	wrefresh(this->map);
	wrefresh(this->stat);
	wrefresh(this->message);
}

Screen::~Screen()
{
	delwin( this->message);
	delwin( this->map);
	delwin( this->stat);
	nocbreak();
	echo();
	curs_set(1);
	endwin();
}

int Screen::getInput()
{
	return getch();
}

void Screen::draw(int px, int py, struct Tile **map)
{
	wclear(this->map);
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x<80; x++)
		{
			mvwprintw(this->map, y, x, &map[y][x].c);
		}
	}
        wattron(this->map, COLOR_PAIR(1));
        mvwprintw(this->map, py, px, "@");
        wattroff(this->map, COLOR_PAIR(1));

	wrefresh(stdscr);
	wrefresh(this->map);
}

void Screen::pMessage(char *message)
{
	mvwprintw(this->message, 0, 1, message);
}

void Screen::refreshMessage(){ wrefresh(this->message);}

void Screen::clearMessage(){ wclear(this->message);}

void Screen::printStat(Player *p)
{
	wclear(this->stat);
	mvwprintw(this->stat, 0, 1, "Strength: %d Intelligience: %d Magic: %d x: %d y: %d", p->Str, p->Int, p->Mp, p->x, p->y);
	wrefresh(this->stat);
}
