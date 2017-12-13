//
// Created by cho on 17. 11. 26.
//

#include "PointBuilderRandom.h"

using namespace std;

PointBuilderRandom::PointBuilderRandom() : PointBuilderRandom(0, 100) {
}

PointBuilderRandom::PointBuilderRandom(double start, double end) :
	_logger{ log4cplus::Logger::getInstance( LOG4CPLUS_TEXT("PointBuilder")) },
	_start{start}, _end{end},
	_gen{random_device()()},
	_distribution{_start, _end} {

	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
}

PointBuilderRandom::~PointBuilderRandom() {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
}

PointPtr PointBuilderRandom::getNext() {
	return PointPtr( new Point(getRandomCordiante()) ) ;
}

