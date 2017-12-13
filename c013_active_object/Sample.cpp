/*
 * SampleRunnable.cpp
 *
 *  Created on: 2016. 12. 4.
 *      Author: cho
 */

#include "Sample.h"

Sample::Sample( const std::string& name ) : ActiveObject(name) {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
}

Sample::~Sample() {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
}

bool Sample::doInitilize() {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
	return true;
}

bool Sample::doRun() {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
	return true;
}

bool Sample::doFinalize() {
	LOG4CPLUS_TRACE( _logger, __PRETTY_FUNCTION__ );
	return true;
}
