//
// Created by cho on 17. 11. 26.
//

#include "BuilderRandom.h"

using namespace std;

BuilderRandom::BuilderRandom() : BuilderRandom(0, 100) {
}

BuilderRandom::BuilderRandom(double max_x, double max_y) :
	_logger{ log4cplus::Logger::getInstance( LOG4CPLUS_TEXT("BuilderRandom")) },
	_max_x{max_x}, _max_y{max_y},
	_gen{random_device()()},
	_distribution_x{-_max_x, _max_x},
	_distribution_y{-_max_y, _max_y} {

	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
}

BuilderRandom::~BuilderRandom() {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
}

ActivePointPtr BuilderRandom::getNext(int type) {
	switch( type ) {
	case Type::CLOCKWISE:        return getClockwise();        break;
	case Type::COUNTERCLOCKWISE: return getCounterClockwise(); break;
	case Type::STOPPED:
	default :                    return getStopped();          break;
	}
}

ActivePointPtr BuilderRandom::getClockwise() {
	// position
	Element pos = Element( _distribution_x(_gen), _distribution_y(_gen) );

	// velocity
	Element vel = Element( - pos.y, pos.x );

	return ActivePointPtr(	new ActivePoint( pos, vel ) ) ;
}

ActivePointPtr BuilderRandom::getCounterClockwise() {
	// position
	Element pos = Element( _distribution_x(_gen), _distribution_y(_gen) );

	// velocity
	Element vel = Element( pos.y, - pos.x );

	return ActivePointPtr(	new ActivePoint( pos, vel ) ) ;
}

ActivePointPtr BuilderRandom::getStopped() {
	// position
	Element pos = Element( _distribution_x(_gen), _distribution_y(_gen) );

	return ActivePointPtr(	new ActivePoint( pos ) ) ;
}

