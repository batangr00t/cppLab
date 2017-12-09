#ifndef CPPLAB_REDISREPLY_H_
#define CPPLAB_REDISREPLY_H_
#include <iostream>
#include <vector>
#include <string>
#include <log4cplus/loggingmacros.h>
#include <hiredis/hiredis.h>

#include "BinString.h"

using namespace std;

class RedisReply {
public:
	RedisReply() = delete;	
	RedisReply(redisReply*);	
	RedisReply(void*);	
	virtual ~RedisReply();
	long long getInteger();
	BinString getBinString() const;
	vector<RedisReply> getArray() const;
	static const string getTypeName( int );
	friend ostream& operator<< ( ostream& os, const RedisReply& );
private:
	log4cplus::Logger _logger;
	redisReply* _reply;

};

#endif /* CPPLAB_REDISREPLY_H_ */
