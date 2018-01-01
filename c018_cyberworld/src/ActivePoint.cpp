//
// Created by cho on 17. 11. 26.
//

#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

#include "ActivePoint.h"
#include "Define.h"
#include "World.h"

using namespace std;

int ActivePoint::_seq = 0;

ActivePoint::ActivePoint() :
	ActivePoint(Element{0,0}, Element{0,0}, 1) {
}

ActivePoint::ActivePoint(const Element& p) :
	ActivePoint(p, Element{0,0}, 1){
}

ActivePoint::ActivePoint(const Element& p, const Element& v) :
	ActivePoint(p, v, 1){
}

ActivePoint::ActivePoint(const Element& p, const Element& v, double mass ) :
	ActiveObject{to_string(++_seq)},
	_mass{ mass },
	_p{p},
	_v{v},
	_lastTime{ chrono::steady_clock::now() } {
	LOG4CPLUS_INFO( _logger, *this << __PRETTY_FUNCTION__ );
}

ActivePoint::~ActivePoint() {
	LOG4CPLUS_INFO( _logger, *this << __PRETTY_FUNCTION__ );

	wait();

	LOG4CPLUS_INFO( _logger, *this << " end ----" );
}

bool ActivePoint::doRun() {
	LOG4CPLUS_TRACE( _logger, *this << __PRETTY_FUNCTION__ );

	// 1. get world
	World& w = World::getInstance();

	// loop for one cycle
	constexpr double T         = 1.0 / Hz;
	unsigned int     loopCount = T/timeSlice;
	LOG4CPLUS_DEBUG( _logger, "loopCount = " << loopCount );

	for ( unsigned int step = 0; step < loopCount; ++step ) {
		// 2. get the force dependent on this object, especially the position
		auto force = w.getForce( *this );

		// 3. calculate acceleration a = F/m
		double ax = force.first  / _mass;
		double ay = force.second / _mass;

		// 4. calculate new position s = s0 + v0 * t + 1/2 * a * t^2
		//                             = s0 + ( v0 + 1/2*a*t ) * t
		_p.x += ( _v.x + 1.0 / 2.0 * ax * timeSlice ) * timeSlice;
		_p.y += ( _v.y + 1.0 / 2.0 * ay * timeSlice ) * timeSlice;

		// 5. calculate new velocity v = v0 + a*t
		_v.x += ax * timeSlice;
		_v.y += ay * timeSlice;
	}

	LOG4CPLUS_DEBUG( _logger, "vx=" << _v.x << " vy=" << _v.y  );
	LOG4CPLUS_DEBUG( _logger, "x=" << _p.x << " y=" << _p.y  );

	return true;
}

std::ostream& operator<<( std::ostream& os, const ActivePoint& ap) {
	os << std::setprecision(1) << std::setfill('0')
	   << "{p" << ap._p << ",v" << ap._v << "," << ap._mass << "}";
	return os;
}
