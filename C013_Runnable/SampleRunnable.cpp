/*
 * SampleRunnable.cpp
 *
 *  Created on: 2016. 12. 4.
 *      Author: cho
 */

#include "SampleRunnable.h"

SampleRunnable::SampleRunnable( const std::string& name ) : _name(name) {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
}

SampleRunnable::~SampleRunnable() {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
}

bool SampleRunnable::doInitilize() {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
	return true;
}

bool SampleRunnable::doRun() {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
	return true;
}

bool SampleRunnable::doFinalize() {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
	return true;
}
