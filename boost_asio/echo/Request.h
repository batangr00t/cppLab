/*
 * Codec.h
 *
 *  Created on: 2017. 3. 11.
 *      Author: cho
 */

#ifndef BOOST_ASIO_ECHO_CODEC_H_
#define BOOST_ASIO_ECHO_CODEC_H_

#include <log4cplus/loggingmacros.h>

// packet format ( fixed length format )
// (3) char 'CHO'    - start
// (1) char 'H'      - header
// (1) unsigned short - body size
// (1) char          - command        'T':get time, 'B':get Big data
// (1) char          - control        'A':ack, 'N':nak
// (N) char []       - body
// (1) char 'T'      - tail

enum DecodeState {
	START,
	HEADER,
	SIZE,
	BODY,
	TAIL,
	COMPLETE,
	INVALID
};

class Request {
public:
	Request();
	virtual ~Request();

	// decode, recvbuf -> request
	DecodeState parse(char * buf, size_t length );
	DecodeState state() const;
	void reset();

	char command() const;
	char control() const;
	const std::vector<char>& body() const;


private:
	// logger
	log4cplus::Logger _logger;

	// decode state
	DecodeState _decodeState = START;

	// received data
	std::vector<char> _start;
	unsigned short    _size;
	char              _command;
	char              _control;
	std::vector<char> _body;

    // private method
	DecodeState _putChar( char c );

	friend std::ostream& operator<<( std::ostream& os, const Request& req );
};

#endif /* BOOST_ASIO_ECHO_CODEC_H_ */
