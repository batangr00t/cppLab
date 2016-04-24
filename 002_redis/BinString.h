/*
 * BinString.h
 *
 *  Created on: 2016. 4. 24.
 *      Author: juik
 */

#ifndef CPPLAB_REDIS_BINSTRING_H_
#define CPPLAB_REDIS_BINSTRING_H_

#include <vector>
#include <string>
#include <log4cplus/loggingmacros.h>

using namespace std;

class BinString {
public:
	BinString() = delete;
	BinString(const BinString&);
	BinString(const size_t,  const char *);
	virtual ~BinString();
	string castString() const;
	template <typename T>
	T castAny() const {
		return *(T*)_str;
	};

	friend ostream& operator<< ( ostream& os, const BinString& );
private:
	static log4cplus::Logger logger;
	const size_t _len;           // read only member variable.
	const char * const _str;     // read only member variable. and const pointer.
};

#endif /* CPPLAB_REDIS_BINSTRING_H_ */
