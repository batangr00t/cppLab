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

DecodeState Request::decode(char * buf, size_t length ) {
	DecodeState result;

	if ( buf == nullptr ) {
		LOG4CPLUS_ERROR(_logger, "buf is nullptr" );
		return PARSING_ERROR;
	}

	for ( size_t i = 0;  i<length; ++i ) {
		result = _putChar( *(buf+i) );
		if ( result == COMPLETE || result == PARSING_ERROR ) break;
	}
	return result;
}

DecodeState Request::state() const {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
	return _decodeState;
}

void Request::reset() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
	_decodeState = START1;
	_parsingError = 0;

	_header = {};
	_body.clear();
}

DecodeState Request::_putChar( char c ) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );

	switch ( _decodeState ) {
	case START1 :
		_header.push_back( c );
		if ( c == STX1) _decodeState = START2;
		break;
	case START2 :
		_header.push_back( c );
		if ( c == STX2) {
			_decodeState = START3;
		} else {
			_decodeState = START1;
		}
		break;
	case START3 :
		_header.push_back( c );
		if ( c == STX3) {
			_decodeState = HEADER;
		} else {
			_decodeState = START1;
		}
		break;
	case HEADER :
		_header.push_back( c );
		LOG4CPLUS_DEBUG(_logger, "_header size = " << _header.size() );
		if ( _header.size() == HEADER_SIZE ) {
			_decodeState = BODY;

			// invalid command
			if ( !_header.checkCommand() ) {
				_parsingError = 1;
			}

			if ( !_header.checkControl() ) {
				_parsingError = 2;
			}

			// invalid body length -> skip parsing
			if ( !_header.checkBodyLen() ) {
				_decodeState = PARSING_ERROR;
			}
		}
		break;
	case BODY :
		_body.push_back(c);
		if ( _body.size() == _header.getBodyLen() ) {
			_decodeState = COMPLETE;
		}
		break;
	default:
		_decodeState = PARSING_ERROR;
	}

	LOG4CPLUS_DEBUG(_logger, "putChar '" << c << "' - " << _decodeState );
	return _decodeState;

}

char Request::command() const {
	return _header.getCommand();
}

char Request::control() const {
	return _header.getControl();
}

const std::vector<char>& Request::body() const {
	return _body;
}

std::ostream& operator<< ( std::ostream& os, const DecodeState& state ) {
	switch ( state ) {
	case START1: 		os << "START1"; 		break;
	case START2: 		os << "START2"; 		break;
	case START3: 		os << "START3"; 		break;
	case HEADER:		os << "HEADER"; 		break;
	case BODY:			os << "BODY";   		break;
	case COMPLETE:		os << "COMPLETE"; 		break;
	case PARSING_ERROR:	os << "PARSING_ERROR"; 	break;
	default:			os << "UNKNOWN"; 		break;
	}

	return os;
}

//std::vector<char> _start;
//unsigned short    _size;
//char              _command;
//char              _control;
//std::vector<char> _body;
std::ostream& operator<<( std::ostream& os, const Request& req ) {
	os << "Request{";
	os << req._header;
	os << ",body[";
	for ( const auto& e : req._body ) os << e;
	os << "]}";

	return os;
}
