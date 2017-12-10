//
// Created by cho on 17. 11. 26.
//

#include "PointBuilder.h"

using namespace std;

PointBuilder::PointBuilder() : PointBuilder(0, 100) {
}

PointBuilder::PointBuilder(double start, double end) :
	_logger{ log4cplus::Logger::getInstance( LOG4CPLUS_TEXT("PointBuilder")) },
	_start{start}, _end{end},
	_gen{random_device()()},
	_distribution{_start, _end} {

	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
}

PointBuilder::~PointBuilder() {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
}

PointPtr PointBuilder::getNext() {
	return PointPtr( new Point(getRandomCordiante()) ) ;
}

