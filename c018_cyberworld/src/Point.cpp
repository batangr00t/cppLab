//
// Created by cho on 17. 11. 26.
//
#include <iomanip>
#include "Point.h"
#include "World.h"
#include "Define.h"

using namespace std;

int Point::_seq = 1;

Point::Point() : Point{0,0} {
}

Point::Point(const std::pair<double, double>& c) : Point{c.first, c.second} {
}

Point::Point(double x, double y) :
	ActiveObject{to_string(++_seq)},
	_mass{1},
	_x(x), _y(y),
	_lastTime{chrono::steady_clock::now()} {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
}

Point::~Point() {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );

	_wait();

	LOG4CPLUS_INFO( _logger, *this << " end ----" );
}

bool Point::doRun() {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );

	// 1. get world
	World& w = World::getInstance();

	// 2. get force
	auto force = w.getForce( *this );

	// 3. calculate a = F/m
	double ax = force.first  / _mass;
	double ay = force.second / _mass;
	LOG4CPLUS_DEBUG( _logger, "fx=" << force.first << " fy=" << force.second  );

	// 4. calculate new s = v0 * t + 1/2 * a * t^2 = ( v0 + 1/2*a*t ) * t
	constexpr double dt = 1.0/Hz;
	LOG4CPLUS_DEBUG( _logger, "dt=" << dt );
	_x += ( _vx + 1.0 / 2.0 * ax * dt ) * dt;
	_y += ( _vy + 1.0 / 2.0 * ay * dt ) * dt;
	LOG4CPLUS_DEBUG( _logger, "x=" << _x << " y=" << _y  );

	// 5. calculate new v = a*t
	_vx += ax * dt;
	_vy += ay * dt;
	LOG4CPLUS_DEBUG( _logger, "vx=" << _vx << " vy=" << _vy  );

	return true;
}

bool operator<( const Point& lhs, const Point& rhs ) {
	return std::tie(lhs._x, lhs._y) < std::tie(rhs._x, rhs._y);
}

std::ostream& operator<<( std::ostream& os, const Point& p) {
	os << std::setprecision(1) << std::setfill('0') << "(" << p._x << "," << p._y << ")";
	return os;
}
