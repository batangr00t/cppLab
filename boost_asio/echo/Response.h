/*
 * Codec.h
 *
 *  Created on: 2017. 3. 11.
 *      Author: cho
 */

#ifndef BOOST_ASIO_ECHO_RESPONSE_H_
#define BOOST_ASIO_ECHO_RESPONSE_H_

#include "MyHeader.h"
#include <log4cplus/loggingmacros.h>

// packet format
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
	Response( const char * data, size_t size );
	virtual ~Response();

	// encode, response -> sendbuf
	//bool encode(char * sendbuf, size_t length);
	void reset();

	MyHeader          header;
	std::vector<char> body;

	friend std::ostream& operator<<( std::ostream& os, const Response& res );
private:
	// logger
	log4cplus::Logger _logger;

};

#endif /* BOOST_ASIO_ECHO_RESPONSE_H_ */
