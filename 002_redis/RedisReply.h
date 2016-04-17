#ifndef REDISREPLY_H_
#define REDISREPLY_H_
#include <iostream>
#include <log4cplus/loggingmacros.h>
#include <hiredis/hiredis.h>

using namespace std;

class RedisReply {
public:
	RedisReply() = delete;	
	RedisReply(RedisReply&) = delete;	
	RedisReply(redisReply*);	
	RedisReply(void*);	
	virtual ~RedisReply();
	string getValue();
	void free();
	friend ostream& operator<< ( ostream& os, const RedisReply& );
private:
	static log4cplus::Logger logger;
	redisReply* _reply;
};

#endif /* REDISREPLY_H_ */
