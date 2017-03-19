/*
 * Codec.cpp
 *
 *  Created on: 2017. 3. 11.
 *      Author: cho
 */

#include "Response.h"

Response::Response()
	: _logger( log4cplus::Logger::getInstance("echo.Response")) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
	reset();
}

Response::Response( const char * data, size_t size )
	: _logger( log4cplus::Logger::getInstance("echo.Response")) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
	reset();

	if ( size >= HEADER_SIZE ) {
		for ( size_t i=0; i<HEADER_SIZE; ++i) {
			header.push_back( data[i] );
		}

		for ( size_t i=HEADER_SIZE; i<size; ++i) {
			body.push_back( data[i] );
		}
	}
}

Response::~Response() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
}

void Response::reset() {
	header.clear();
	body.clear();
}

std::ostream& operator<<( std::ostream& os, const Response& res ) {
	os << "Response{";
	os << res.header;
	os << ",body[";
	for ( const auto& e : res.body ) os << e;
	os << "]}";

	return os;
}
