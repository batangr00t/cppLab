/*
 * Codec.h
 *
 *  Created on: 2017. 3. 11.
 *      Author: cho
 */

#ifndef BOOST_ASIO_ECHO_CODEC_H_
#define BOOST_ASIO_ECHO_CODEC_H_

#include <log4cplus/loggingmacros.h>
#include "MyHeader.h"

enum DecodeState {
	START1,
	START2,
	START3,
	HEADER,
	BODY,
	COMPLETE,
	PARSING_ERROR
};

std::ostream& operator<< ( std::ostream& os, const DecodeState& state );

class Request {
public:
	Request();
	virtual ~Request();

	// decode, recvbuf -> request
	DecodeState decode(char * buf, size_t length );
	DecodeState state() const;
	void reset();

	char command() const;
	char control() const;
	const std::vector<char>& body() const;

	uint8_t getParsingError() const;

private:
	// logger
	log4cplus::Logger _logger;

	// decode state
	DecodeState _decodeState = START1;
	uint8_t     _parsingError = 0;   // 0=success, else error code

	// received data
	MyHeader         _header;
	std::vector<char> _body;

    // private method
	DecodeState _putChar( char c );

	friend std::ostream& operator<<( std::ostream& os, const Request& req );
};

#endif /* BOOST_ASIO_ECHO_CODEC_H_ */
