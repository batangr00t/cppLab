/*
 * Runnable.cpp
 *
 *  Created on: 2016. 12. 4.
 *      Author: cho
 */

#include "Runnable.h"

Runnable::Runnable()
: _logger(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Runnable"))) {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
}

Runnable::~Runnable() {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
}

// control method
// initialize
void Runnable::init() {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
	if ( doInitilize() ) {
		LOG4CPLUS_INFO( _logger, "init success" );
	} else {
		doFinalize();
		LOG4CPLUS_ERROR( _logger, "init error" );
	}
}

// start main loop
void Runnable::start() {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
	if ( doRun() ) {
		LOG4CPLUS_INFO( _logger, "start success" );
	} else {
		doFinalize();
		LOG4CPLUS_ERROR( _logger, "start error" );
	}
}

// stop thread
void Runnable::stop() {
	LOG4CPLUS_INFO( _logger, __PRETTY_FUNCTION__ );
	if ( doFinalize() ) {
		LOG4CPLUS_INFO( _logger, "stop success" );
	} else {
		LOG4CPLUS_ERROR( _logger, "stop error" );
	}
}

// monitoring just for debug
std::string Runnable::getState() {
	return "not yet implemented.";
}
