/*
 * ActiveObject.cpp
 *
 *  Created on: 2017. 12. 13.
 *      Author: cho
 */

#include "ActiveObject.h"
#include "Define.h"

using namespace std;

ActiveObject::ActiveObject(const std::string& name) :
	_logger{ log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("ActiveObject")) },
	_name{ name },
	_state{ State::CREATED } {
	LOG4CPLUS_INFO( _logger, *this << __FUNCTION__ );

	try {
		_main_loop_result = async( launch::async, &ActiveObject::_main, this );
	} catch( const exception& e ) {
		LOG4CPLUS_ERROR( _logger, e.what() );
	}
}

ActiveObject::~ActiveObject() {
	LOG4CPLUS_INFO( _logger, *this << __FUNCTION__ );

}

void ActiveObject::init() {
	_state = State::INITIALIZING;
	LOG4CPLUS_TRACE( _logger, *this << __FUNCTION__ );
}

void ActiveObject::start() {
	_state = State::RUNNING;
	LOG4CPLUS_TRACE( _logger, *this << __FUNCTION__ );
}

void ActiveObject::stop() {
	_state = State::FINALIZING;
	LOG4CPLUS_TRACE( _logger, *this << __FUNCTION__ );
}

// protected
void ActiveObject::_wait() {
	try {
		future_status status = _main_loop_result.wait_for( chrono::milliseconds(2000) );
		if ( status == future_status::ready ) {
			LOG4CPLUS_DEBUG( _logger, "future_status::ready " << *this );
			_main_loop_result.get();
		} else if ( status == future_status::timeout ) {
			LOG4CPLUS_WARN( _logger, "future_status::timeout " << *this );
		} else if ( status == future_status::deferred ) {
			LOG4CPLUS_WARN( _logger, "future_status::deferred " << *this );
		}
	} catch( const exception& e ) {
		LOG4CPLUS_ERROR( _logger, e.what() );
	}
}

// private
bool ActiveObject::_main() {
	LOG4CPLUS_TRACE( _logger, *this << __FUNCTION__ );

	while( _state != State::STOPPED ) {
		this_thread::sleep_for( chrono::milliseconds(1000/Hz) );

		switch ( _state ) {
		case ActiveObject::State::CREATED:
			LOG4CPLUS_DEBUG( _logger, *this << " enter the main_loop!" );
			break;

		case ActiveObject::State::INITIALIZING :
			if ( doInitilize() ) {
				LOG4CPLUS_DEBUG( _logger, *this << " doInitilize() succeed" );
				_state = State::READY;
			} else {
				LOG4CPLUS_ERROR( _logger, *this << " doInitilize() failed" );
				_state = State::FINALIZING;
			}
			break;

		case ActiveObject::State::READY:
			LOG4CPLUS_DEBUG( _logger, *this << " waiting for start..." );
			break;

		case ActiveObject::State::RUNNING:
			if ( doRun() ) {
				LOG4CPLUS_DEBUG( _logger, *this << " doRun() succeed" );
			} else {
				LOG4CPLUS_ERROR( _logger, *this << " doRun() failed" );
				_state = State::FINALIZING;
			}
			break;

		case ActiveObject::State::FINALIZING   :
			if ( doFinalize() ) {
				LOG4CPLUS_DEBUG( _logger, *this << " doFinalize() succeed" );
			} else {
				LOG4CPLUS_ERROR( _logger, *this << " doFinalize() failed" );
			}
			_state = State::STOPPED;
			break;

		case ActiveObject::State::STOPPED      :
		default                                :
			break;
		}
	}

	return true;
}

std::ostream& operator<<( std::ostream& os, const ActiveObject& object ) {
	os << "AO(\"" << object._name << "\"," << object._state << ")";
	return os;
}

std::ostream& operator<<( std::ostream& os, const ActiveObject::State& state ) {
	switch ( state ) {
	case ActiveObject::State::CREATED      : os << "CREATED";      break;
	case ActiveObject::State::INITIALIZING : os << "INITIALIZING"; break;
	case ActiveObject::State::READY        : os << "READY";        break;
	case ActiveObject::State::RUNNING      : os << "RUNNING";      break;
	case ActiveObject::State::FINALIZING   : os << "FINALIZING";   break;
	case ActiveObject::State::STOPPED      : os << "STOPPED";      break;
	default                                : os << "UNKNOWN";      break;
	}

	return os;
}

