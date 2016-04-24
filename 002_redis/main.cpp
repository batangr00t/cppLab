#include <iostream>
#include <string>
#include <vector>
#include <hiredis/hiredis.h>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>

#include "RedisReply.h"
#include "BinString.h"

using namespace std;

log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main"));

int main(int argc, char *argv[]) {
	cout << "---------------- start program ------------" << endl;
	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");

	unsigned int j;
	redisContext *c;

	unsigned int count = ( argc > 1 ) ? atoi(argv[1]) : 100;

	string const hostname("127.0.0.1");
	int port = 6379;

	struct timeval timeout = { 1, 500000 }; //1.5 count
	cout << "1. ------ connect" << endl;
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

	cout << "2. ------ get" << endl;
	const string GET("GET bar");
	cout << "Command \""<< GET << "\" " << count << " times" << endl;
	for ( j=0; j<count; j++ ) {
		RedisReply replyWrapper(redisCommand( c, GET.c_str()) );
		cout << replyWrapper << endl;
		BinString binStr = replyWrapper.getBinString();
		cout << binStr.castString() << endl;
	}

	cout << "3. ------ mget " << endl;
	const string MGET("MGET foo bar bar bar");
	cout << "Command \""<< MGET << "\" " << count << " times" << endl;
	for ( j=0; j<count; j++ ) {
		RedisReply replyWrapper(redisCommand( c, MGET.c_str()) );
		cout << replyWrapper << endl;
		vector<BinString> binStrs = replyWrapper.getArray();
		cout << "3." << j << " display ----" << endl;
		for ( const BinString& bs: binStrs ) {
			cout << bs.castString() << endl;
			cout << bs.castAny<int>() << endl;
			cout << bs.castAny<long>() << endl;
			cout << bs.castAny<float>() << endl;
			cout << bs.castAny<double>() << endl;
		}
	}
	cout << "3. ------ free context" << endl;
	redisFree(c);

	cout << "---------------- end    program ------------" << endl;
	return 0;
}
