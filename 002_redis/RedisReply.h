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
	RedisReply(RedisReply&) = delete;	
	RedisReply(redisReply*);	
	RedisReply(void*);	
	virtual ~RedisReply();
	long long getInteger();
	BinString getBinString();
	vector<BinString> getArray();
	static const string getTypeName( int );
	friend ostream& operator<< ( ostream& os, const RedisReply& );
private:
	log4cplus::Logger _logger;
	redisReply* _reply;

};

#endif /* CPPLAB_REDISREPLY_H_ */
