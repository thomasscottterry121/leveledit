#include<screen.h>

Screen::Screen(){
	initscr();
	cbreak();
	noecho();
	curs_set(0);

	this->message = newwin(1,79,0,0);
	this->map = newwin(20, 79, 1, 0);
	this->stat = newwin(3, 79, 21, 0);
	wclear(stdscr);
	wrefresh(stdscr);
	wclear(this->message);
	wclear(this->stat);
	wclear(this->map);
	wrefresh(this->map);
	wrefresh(this->stat);
	wrefresh(this->message);
}

Screen::~Screen(){
	delwin( this->message);
	delwin( this->map);
	delwin( this->stat);
	nocbreak();
	echo();
	curs_set(1);
	endwin();
}

int Screen::getInput(){
	return getch();
}

void Screen::draw(Game *g){
	wclear(this->map);
	mvwprintw(this->map,g->playerY, g->playerX, "@");
	wrefresh(stdscr);
	wrefresh(this->map);
}
