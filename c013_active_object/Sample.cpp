/*
 * SampleRunnable.cpp
 *
 *  Created on: 2016. 12. 4.
 *      Author: cho
 */

#include "Sample.h"

using namespace std;

Sample::Sample( const std::string& name ) : ActiveObject(name) {
	LOG4CPLUS_TRACE( _logger, *this << __FUNCTION__ );
}

Sample::~Sample() {
	LOG4CPLUS_TRACE( _logger, *this << __FUNCTION__ << " waits for parent's thread termination...");

	_wait();

	LOG4CPLUS_TRACE( _logger, *this << __FUNCTION__ << " finished ...");
}

bool Sample::doInitilize() {
	LOG4CPLUS_TRACE( _logger, *this << __FUNCTION__ );
	return true;
}

bool Sample::doRun() {
	LOG4CPLUS_TRACE( _logger, *this << __FUNCTION__ );
	return true;
}

bool Sample::doFinalize() {
	LOG4CPLUS_TRACE( _logger, *this << __FUNCTION__ );
	return true;
}

ostream& operator<<(ostream& os, const Sample& sample ) {
	os << "Sample(\"" << sample.getName() << "\"," << sample.getState() << ")";
	return os;
}
