/*
 * Codec.h
 *
 *  Created on: 2017. 3. 11.
 *      Author: cho
 */

#ifndef BOOST_ASIO_ECHO_RESPONSE_H_
#define BOOST_ASIO_ECHO_RESPONSE_H_

#include <log4cplus/loggingmacros.h>

// packet format ( fixed length format )
// (3) char 'CHO'    - start
// (1) char 'H'      - header
// (1) unsigned short - body size
// (1) char          - command 'T':get time, 'B':get Big data
// (1) char          - status  'B':bad command
// (N) char []       - body
// (1) char 'T'      - tail

class Response {
public:
	Response();
	virtual ~Response();

	// encode, response -> sendbuf
	bool encode(char * sendbuf, size_t length);
	void reset();

private:
	// logger
	log4cplus::Logger _logger;

	// send data
	char              _status;
	char              _control;
	std::vector<char> _body;
};

#endif /* BOOST_ASIO_ECHO_RESPONSE_H_ */
