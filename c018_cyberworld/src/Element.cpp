/*
 * Point.cpp
 *
 *  Created on: 2017. 12. 17.
 *      Author: cho
 */

#include "Element.h"

Element::Element() : Element(0.0, 0.0) {
}

Element::Element(double xval, double yval) :
	x{xval}, y{yval},
	_logger{ log4cplus::Logger::getInstance("Element") } {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
}

Element::~Element() {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
}

std::ostream& operator<<( std::ostream& os, const Element& p ) {
	os << "(" << p.x << "," << p.y << ")";
	return os;
}
