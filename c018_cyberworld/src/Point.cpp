//
// Created by cho on 17. 11. 26.
//

#include "Point.h"

Point::Point() : Point(0,0) {
	LOG4CPLUS_TRACE( logger, __PRETTY_FUNCTION__ );
}

Point::Point(double x, double y) :
	logger( log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Point"))),
	x(x), y(y){
	LOG4CPLUS_TRACE( logger, __PRETTY_FUNCTION__ );
}

Point::~Point() {
	LOG4CPLUS_TRACE( logger, __PRETTY_FUNCTION__ );
}

bool operator<( const Point& lhs, const Point& rhs ) {
	return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
}

std::ostream& operator<<( std::ostream& os, const Point& p) {
	os << "(" << p.x << "," << p.y << ")";
	return os;
}
