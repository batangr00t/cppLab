/*
 * Screen.cpp
 *
 *  Created on: 2017. 12. 16.
 *      Author: cho
 */

#include <thread>
#include <ncurses.h>
#include "Screen.h"
#include "World.h"

using namespace std;

Screen::Screen() :
	_logger( log4cplus::Logger::getInstance( LOG4CPLUS_TEXT("Screen"))) {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );

	initscr();
	nodelay(stdscr, true);
	keypad(stdscr, true);
	noecho();
	curs_set(0);
	getmaxyx( stdscr, _maxHeight, _maxWidth);
	LOG4CPLUS_INFO( _logger, " maxHeight="<< _maxHeight << ", maxWidth=" << _maxWidth );

	fence();
	refresh();
}

Screen::~Screen() {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
	nodelay(stdscr, false);
	getch();
	endwin();
}

std::pair<int,int> Screen::getSize() const {
	return make_pair(_maxHeight, _maxWidth );
}

// fence
void Screen::fence(char material) {
	// left, right
	for( int i = 0; i < _maxHeight; ++i ) {
		mvaddch(i, 0, material );
		mvaddch(i, _maxWidth-1, material );
	}

	// top, down
	for( int i = 0; i < _maxWidth; ++i ) {
		mvaddch(0, i, material );
		mvaddch(_maxHeight-1, i, material );
	}
}

// axis
void Screen::axes(char material) {
	// y axis
	for( int i = 1; i < _maxHeight-1; ++i ) {
		mvaddch(i, _maxWidth/2, material );
	}

	// x axis
	for( int i = 1; i < _maxWidth-1; ++i ) {
		mvaddch( _maxHeight/2, i, material );
	}

	mvaddch(_maxHeight/2, _maxWidth/2, '0' );
}

void Screen::clear() {
	// left, right
	for( int i = 1; i < _maxHeight-1; ++i ) {
		for ( int j = 1; j < _maxWidth -1; ++j ) {
			mvaddch( i, j, ' ' );
		}
	}
}

int Screen::showWorld() {
	World& world = World::getInstance();

	clear();
	axes();
	for ( const auto& ap: world.getActivePoints() ) {
		move(ap->getPoint().y + _maxHeight/2, ap->getPoint().x + _maxWidth/2 );
		printw( ap->getName().c_str() );
	}
	fence();
	refresh();

	LOG4CPLUS_TRACE( _logger, world );
	return getch();
}

// show the world
// figlet -f smslant Juik World
void Screen::showTitle(unsigned int durationMs) {
	int row = _maxHeight/2 - 2;
	int col = _maxWidth/2 - 25;
    mvprintw(row+0, col, R"(     __     _ __     _      __         __   __   ____ )");
    mvprintw(row+1, col, R"( __ / /_ __(_) /__  | | /| / /__  ____/ /__/ /  / / / )");
    mvprintw(row+2, col, R"(/ // / // / /  '_/  | |/ |/ / _ \/ __/ / _  /  /_/_/  )");
    mvprintw(row+3, col, R"(\___/\_,_/_/_/\_\   |__/|__/\___/_/ /_/\_,_/   0 0    )");
	refresh();
	this_thread::sleep_for( chrono::milliseconds(durationMs));
}

// show ending credit
// figlet -f smslant Good Bye
void Screen::showEnding(unsigned int durationMs) {
	clear();
	fence();

	int row = _maxHeight/2 - 10;
	int col = _maxWidth/2 - 20;
    mvprintw(row+0 , col, R"(  _____             __  ___                  )");
    mvprintw(row+1 , col, R"( / ___/__  ___  ___/ / / _ )__ _____    ____ )");
    mvprintw(row+2 , col, R"(/ (_ / _ \/ _ \/ _  / / _  / // / -_)  / / / )");
    mvprintw(row+3 , col, R"(\___/\___/\___/\_,_/ /____/\_, /\__/  /_/_/  )");
    mvprintw(row+4 , col, R"(                          /___/       0 0    )");


    mvprintw(row+7 , col, R"(           Producer   Juik Cho.              )");
    mvprintw(row+8 , col, R"(           Architect  Juik Cho.              )");
    mvprintw(row+9 , col, R"(           Designer   Juik Cho.              )");
    mvprintw(row+10, col, R"(           Programmer Juik Cho.              )");
    mvprintw(row+13, col, R"(             Press any key...                )");
	refresh();
	this_thread::sleep_for( chrono::milliseconds(durationMs));
}

