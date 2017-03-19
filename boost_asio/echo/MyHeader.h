/*
 * Record.h
 *
 *  Created on: 2017. 3. 19.
 *      Author: cho
 */

#ifndef BOOST_ASIO_ECHO_MYHEADER_H_
#define BOOST_ASIO_ECHO_MYHEADER_H_

#include <vector>
#include <iterator>
#include <log4cplus/loggingmacros.h>

// packet format ( fixed length header )
// (3) char [3] - start          'CHO'
// (1) char     - command        'T':get time, 'B':get Big data, 'E': echo, 'X':error
// (1) char     - control        'A':ack, 'N':nak, 'D':data, 'X':error
// (2) uint16_t	- body size
// (N) char []  - body

const char STX1 = 'C';
const char STX2 = 'H';
const char STX3 = 'O';
const size_t HEADER_SIZE = 7;
const size_t BODY_MAX_SIZE = 1024;

class MyHeader : public std::vector<char> {
public:
	// ctor for server
	MyHeader();

	// ctor for client
	MyHeader(char cmd, char cntl, uint16_t len);

	// dtor
	virtual ~MyHeader();

	// set a field
	void putField(char cmd, char cntl, uint16_t len);

	// get a field
	char getCommand() const;
	char getControl() const;
	uint16_t getBodyLen() const; // little endian

	// check a field
	bool checkCommand();
	bool checkControl();
	bool checkBodyLen();
private:
	// logger
	log4cplus::Logger _logger;
};

std::ostream& operator<<( std::ostream& os, const MyHeader& header );

#endif /* BOOST_ASIO_ECHO_MYHEADER_H_ */
