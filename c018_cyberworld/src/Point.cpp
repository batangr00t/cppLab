//
// Created by cho on 17. 11. 26.
//
#include <iomanip>
#include "Point.h"
#include "World.h"

using namespace std;

Point::Point() : Point{0,0} {
}

Point::Point(const std::pair<double, double>& c) : Point{c.first, c.second} {
}

Point::Point(double x, double y) :
	_logger( log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Point"))),
	_mass{1},
	_x(x), _y(y) {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
}

Point::~Point() {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
}

void Point::run() {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );

}

void Point::stop() {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );

}

void Point::move() {
	//LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );

	// 1. current time
	World& w = World::getInstance();
	unsigned int currentTime = w.currentTime();

	// 2. force
	auto force = w.F( *this );

	// 3. a = F/m
	double ax = force.first  / _mass;
	double ay = force.second / _mass;

	// 4. s = 1/2 * a * t^2
	double dt = ( currentTime - _lastTime );
	double t2 = dt*dt;
	_x += 1.0 / 2.0 * ax * t2;
	_y += 1.0 / 2.0 * ay * t2;

	// 5. save last time
	_lastTime = currentTime;
}



bool operator<( const Point& lhs, const Point& rhs ) {
	return std::tie(lhs._x, lhs._y) < std::tie(rhs._x, rhs._y);
}

std::ostream& operator<<( std::ostream& os, const Point& p) {
	os << std::setprecision(2) << std::setfill('0') << "(" << p._x << "," << p._y << ")";
	return os;
}
