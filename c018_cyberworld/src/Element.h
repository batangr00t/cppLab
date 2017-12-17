/*
 * Point.h
 *
 *  Created on: 2017. 12. 17.
 *      Author: cho
 */

#ifndef C018_CYBERWORLD_SRC_ELEMENT_H_
#define C018_CYBERWORLD_SRC_ELEMENT_H_

#include <log4cplus/loggingmacros.h>
#include <cmath>
#include <ostream>

// represent an element of a stuff. in 2 dimension
class Element {
public:
	double x;
	double y;

	Element();
	Element(double x, double y);
	virtual ~Element();

	inline double abs() {
		return sqrt( pow( x, 2) + pow( y, 2) );
	}

	friend std::ostream& operator<<( std::ostream& os, const Element& p );
private:
	log4cplus::Logger _logger;
};

#endif /* C018_CYBERWORLD_SRC_ELEMENT_H_ */
