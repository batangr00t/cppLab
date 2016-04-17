#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <hiredis/hiredis.h>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>

#include "RedisReply.h"

using namespace std;

log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("get"));

int main(int argc, char *argv[]) {
	cout << "---------------- start program ------------" << endl;
	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");

	unsigned int j;
	redisContext *c;

	unsigned int count = ( argc > 1 ) ? atoi(argv[1]) : 100;

	//const char *hostname = "127.0.0.1";
	string const hostname("127.0.0.1");
	int port = 6379;

	struct timeval timeout = { 1, 500000 }; //1.5 count
	c = redisConnectWithTimeout( hostname.c_str(), port, timeout );
	if ( c == NULL || c->err ) { 
		if (c) {
			cout << "Connection error" << c->errstr << endl;
			redisFree(c);
		} else {
			cout << "Connection error : can't allocate redis context" << endl;
		} 
		exit(1);
	}

	//const char *COMMAND = "GET foo";
	const string COMMAND("GET foo");

	for ( j=0; j<count; j++ ) {
		RedisReply replyWrapper(redisCommand( c, COMMAND.c_str()) );
		cout << "before free : " << replyWrapper << endl;
		string value = replyWrapper.getValue();
		cout << value << endl;

		replyWrapper.free();
		cout << "after free : " << replyWrapper << endl;
	}

	cout << "Command \""<< COMMAND << "\" " << count << " times" << endl;

	redisFree(c);

	cout << "---------------- end    program ------------" << endl;
	return 0;
}
