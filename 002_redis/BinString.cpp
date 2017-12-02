/*
 * BinString.cpp
 *
 *  Created on: 2016. 4. 24.
 *      Author: juik
 */

#include <iomanip>
#include "BinString.h"

BinString::BinString() : BinString("", 0) {
	LOG4CPLUS_TRACE(_logger, this << ":" << __PRETTY_FUNCTION__ );
}

BinString::BinString(const BinString& s) :
	_logger(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("BinString"))),
	 _str(s._str), _len(s._len) {
	LOG4CPLUS_TRACE(_logger, this << ":" << __PRETTY_FUNCTION__ );
}

BinString::BinString(const char* str, const size_t len) : _str(str), _len(len) {
	LOG4CPLUS_TRACE(_logger, this << ":" << __PRETTY_FUNCTION__ );
}

BinString::~BinString() {
	LOG4CPLUS_TRACE(_logger, this << ":" << __PRETTY_FUNCTION__ );
}

string BinString::castString() const {
	return string(_str, _len);
}

ostream& operator<< ( ostream& os, const BinString & binStr ) {
	os << "[" << &binStr << "]{" << binStr._len << ", {";
	os << hex << showbase;
	for ( size_t i =0; i<binStr._len; i++ ) {
		 os << static_cast<int>(binStr._str[i]) << ",";
	}
	os << setbase(0) << ":";
	for ( size_t i=0; i<binStr._len; i++ ) {
		 os << binStr._str[i] << ",";
	}
	os << "}}";

	return os;
}

