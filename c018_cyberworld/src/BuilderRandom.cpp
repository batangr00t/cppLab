//
// Created by cho on 17. 11. 26.
//

#include "BuilderRandom.h"

using namespace std;

BuilderRandom::BuilderRandom() : BuilderRandom(0, 100, Type::MIXED) {
}

BuilderRandom::BuilderRandom(double max_x, double max_y, int type) :
	_logger{ log4cplus::Logger::getInstance( LOG4CPLUS_TEXT("BuilderRandom")) },
	_max_x{max_x}, _max_y{max_y}, _type{type},
	_gen{random_device()()},
	_dis_type{0, Type::SIZE-1},
	_dis_x{-_max_x, _max_x},
	_dis_y{-_max_y, _max_y} {

	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
}

BuilderRandom::~BuilderRandom() {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
}

ActivePointPtr BuilderRandom::getNext() {
	return getNext( _type );
}

ActivePointPtr BuilderRandom::getNext(int type) {
	switch( type ) {
	case Type::CLOCKWISE:        return getClockwise();             break;
	case Type::COUNTERCLOCKWISE: return getCounterClockwise();      break;
	case Type::STOPPED:          return getStopped();               break;
	case Type::MIXED:
	default :                    return getNext( _dis_type(_gen) ); break;
	}
}

ActivePointPtr BuilderRandom::getClockwise() {
	// position
	Element pos = Element( _dis_x(_gen), _dis_y(_gen) );

	// velocity
	Element vel = Element( - pos.y, pos.x );

	return ActivePointPtr(	new ActivePoint( pos, vel ) ) ;
}

ActivePointPtr BuilderRandom::getCounterClockwise() {
	// position
	Element pos = Element( _dis_x(_gen), _dis_y(_gen) );

	// velocity
	Element vel = Element( pos.y, - pos.x );

	return ActivePointPtr(	new ActivePoint( pos, vel ) ) ;
}

ActivePointPtr BuilderRandom::getStopped() {
	// position
	Element pos = Element( _dis_x(_gen), _dis_y(_gen) );

	return ActivePointPtr(	new ActivePoint( pos ) ) ;
}

