/*
 * Screen.h
 *
 *  Created on: 2017. 12. 16.
 *      Author: cho
 */

#ifndef C018_CYBERWORLD_SRC_SCREEN_H_
#define C018_CYBERWORLD_SRC_SCREEN_H_

#include <log4cplus/loggingmacros.h>
#include <utility>

class Screen {
public:
	Screen();
	virtual ~Screen();

	// clear screen except fence
	std::pair<int,int> getSize() const;

	// fence
	void fence(char material = 219);

	// clear screen except fence
	void clear();

	// show the world
	void showWorld();

	// show the world
	void showTitle(unsigned int durationMs = 1000); // show 1sec

	// show ending credit
	void showEnding(unsigned int durationMs = 1000);

private:
	// logger
	log4cplus::Logger _logger;

	// screen size
	int _maxHeight;
	int _maxWidth;

	// a char material used to display a Point in the screen
	char _pointMaterial = 'X';
};

#endif /* C018_CYBERWORLD_SRC_SCREEN_H_ */
