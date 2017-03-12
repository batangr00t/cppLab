/*
 * Codec.cpp
 *
 *  Created on: 2017. 3. 11.
 *      Author: cho
 */

#include "Request.h"

Request::Request()
	: _logger( log4cplus::Logger::getInstance("echo.Request")) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );

	reset();
}

Request::~Request() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
}

DecodeState Request::parse(char * buf, size_t length ) {
	DecodeState result;

	if ( buf == nullptr ) {
		LOG4CPLUS_ERROR(_logger, "buf is nullptr" );
		return INVALID;
	}

	for ( size_t i = 0;  i<length; ++i ) {
		result = _putChar( *(buf+i) );
		if ( result == COMPLETE || result == INVALID ) break;
	}
	return result;
}

DecodeState Request::state() const {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
	return _decodeState;
}

void Request::reset() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
	_start.clear();
	_size = 0;
	_body.clear();
	_decodeState = START;
}

DecodeState Request::_putChar( char c ) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );

	_body.push_back( c );

	switch ( _decodeState ) {
	case START :
		if ( c == 'E' ) {
			_decodeState = COMPLETE;
		};
		break;
	default:
		_decodeState = INVALID;
	}

	LOG4CPLUS_DEBUG(_logger, "putChar '" << c << "' - " << _decodeState );
	return _decodeState;

}

char Request::command() const {
	return _command;
}

char Request::control() const {
	return _control;
}

const std::vector<char>& Request::body() const {
	return _body;
}
