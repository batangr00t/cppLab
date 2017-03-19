/*
 * ChoHeader.cpp
 *
 *  Created on: 2017. 3. 19.
 *      Author: cho
 */

#include "MyHeader.h"

MyHeader::MyHeader()
 	: _logger( log4cplus::Logger::getInstance("echo.MyHeader")) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
}

MyHeader::MyHeader(char cmd, char cntl, uint16_t len)
 	: _logger( log4cplus::Logger::getInstance("echo.MyHeader")) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
	putField( cmd, cntl, len);
}

MyHeader::~MyHeader() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
}

void MyHeader::putField(char cmd, char cntl, uint16_t len) {
	push_back(STX1);
	push_back(STX2);
	push_back(STX3);
	push_back(cmd);
	push_back(cntl);
	push_back( len & 0xff );
	push_back( ( len >> 8 ) & 0xff );
}

char MyHeader::getCommand() const {
	if ( size() > 3 ) {
		return (*this)[3];
	} else {
		return 'X';
	}
}

char MyHeader::getControl() const {
	if ( size() > 4 ) {
		return (*this)[4];
	} else {
		return 'X';
	}
}

// little endian
uint16_t MyHeader::getBodyLen() const {
	if ( size() > 6 ) {
		return (*this)[5] | ( (*this)[6] << 8);
	} else {
		return 0;
	}
}

bool MyHeader::checkCommand() {
	char c = getCommand();

	switch( c ) {
	case 'T':
	case 'B':
	case 'E':
		return true;
	default:
		return false;
	}
}

bool MyHeader::checkControl() {
	char c = getControl();

	switch( c ) {
	case 'A':
	case 'N':
	case 'D':
		return true;
	default:
		return false;
	}
}

bool MyHeader::checkBodyLen() {
	uint16_t len = getBodyLen();

	if ( len > 0 && len <= BODY_MAX_SIZE ) {
		return true;
	} else {
		return false;
	}
}

std::ostream& operator<<( std::ostream& os, const MyHeader& header ) {
	os << "ChoHeader{";
	os << "command:" << header.getCommand();
	os << ",control:" << header.getControl();
	os << ",bodyLen:" << header.getBodyLen();
	os << "}";

	return os;
}


