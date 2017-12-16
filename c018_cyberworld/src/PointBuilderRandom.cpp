//
// Created by cho on 17. 11. 26.
//

#include "PointBuilderRandom.h"

using namespace std;

PointBuilderRandom::PointBuilderRandom() : PointBuilderRandom(0, 100) {
}

PointBuilderRandom::PointBuilderRandom(double max_x, double max_y) :
	_logger{ log4cplus::Logger::getInstance( LOG4CPLUS_TEXT("PointBuilder")) },
	_max_x{max_x}, _max_y{max_y},
	_gen{random_device()()},
	_distribution_x{-_max_x, _max_x},
	_distribution_y{-_max_y, _max_y} {

	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
}

PointBuilderRandom::~PointBuilderRandom() {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
}

PointPtr PointBuilderRandom::getNext() {
	return PointPtr( new Point(getRandomCordiante()) ) ;
}

