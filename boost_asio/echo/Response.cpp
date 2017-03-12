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

Response::~Response() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
}

// encode, response -> sendbuf
bool Response::encode(char * sendbuf, size_t length) {
	return false;
}

void Response::reset() {
	_body.clear();
}
