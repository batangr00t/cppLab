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
	noecho();
	curs_set(0);
	getmaxyx( stdscr, _maxHeight, _maxWidth);
	LOG4CPLUS_INFO( _logger, " maxHeight="<< _maxHeight << ", maxWidth=" << _maxWidth );

	fence();
	refresh();
}

Screen::~Screen() {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
//	nodelay(stdscr, false);
//	getch();
	endwin();
}

std::pair<int,int> Screen::getSize() const {
	return make_pair(_maxHeight, _maxWidth );
}

// fence
void Screen::fence(char material) {
	// left, right
	for( int i = 0; i < _maxHeight; ++i ) {
		move(i, 0);
		addch( material );
		move(i, _maxWidth-1);
		addch( material );
	}

	// top, down
	for( int i = 0; i < _maxWidth; ++i ) {
		move(0, i);
		addch( material );
		move(_maxHeight-1, i);
		addch( material );
	}
}

void Screen::clear() {
	// left, right
	for( int i = 1; i < _maxHeight-1; ++i ) {
		for ( int j = 1; j < _maxWidth -1; ++j ) {
			mvaddch( i, j, ' ' );
		}
	}
}

void Screen::showWorld() {
	World& world = World::getInstance();

	clear();
	for ( const auto& e: world.getPoints() ) {
		move(e->y() + _maxHeight/2, e->x() + _maxWidth/2 );
		printw( e->getName().c_str() );
	}

	LOG4CPLUS_TRACE( _logger, world );

	refresh();
}

// show the world
void Screen::showTitle(unsigned int durationMs) {
	move( _maxHeight/2, _maxWidth/2 - 10 );
	printw( "Welcome to the Juik world!!!");
	refresh();
	this_thread::sleep_for( chrono::milliseconds(durationMs));
}

// show ending credit
void Screen::showEnding(unsigned int durationMs) {
	clear();
	fence();
	move( _maxHeight/2, _maxWidth/2 - 10 );
	printw( "      Good bye!!!           ");
	move( _maxHeight/2+2, _maxWidth/2 - 10 );
	printw( "    Press any key...        ");
	refresh();
	this_thread::sleep_for( chrono::milliseconds(durationMs));
}
