#include <signal.h>
#include <iostream>
#include <string>
#include <vector>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
#include <hiredis/adapters/libevent.h>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <future>

#include "RedisReply.h"
#include "BinString.h"

using namespace std;

log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main"));

void callback(redisAsyncContext *ac, void *r, void *privdata) {
	LOG4CPLUS_TRACE(logger, __PRETTY_FUNCTION__);
	RedisReply reply( r );
    cout << reply << endl;
    this_thread::sleep_for( chrono::milliseconds(200) );
}

void stopCallback(redisAsyncContext *ac, void *r, void *privdata) {
	LOG4CPLUS_TRACE(logger, __PRETTY_FUNCTION__);
	RedisReply reply( r );
    cout << reply << endl;

	redisAsyncDisconnect(ac);
}

void connectCallback(const redisAsyncContext *ac, int status) {
	LOG4CPLUS_TRACE(logger, __PRETTY_FUNCTION__);
    if (status != REDIS_OK) {
    	LOG4CPLUS_ERROR(logger, "Error : " << ( (ac==nullptr) ? "nullptr" : ac->errstr ));
        return;
    }
    LOG4CPLUS_INFO( logger, "Connected..." );
}

void disconnectCallback(const redisAsyncContext *ac, int status) {
	LOG4CPLUS_TRACE(logger, __PRETTY_FUNCTION__);
    if (status != REDIS_OK) {
    	LOG4CPLUS_ERROR(logger, "Error : " << ( (ac==nullptr) ? "nullptr" : ac->errstr ));
        return;
    }
    LOG4CPLUS_INFO(logger, "Disconnected..." );
}

int main() {
	cout << "---------------- start program ------------" << endl;
	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");


    signal(SIGPIPE, SIG_IGN);
    struct event_base *base = event_base_new();

    LOG4CPLUS_DEBUG(logger, "redisAsyncConnect" );
    redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
    if ( ac == nullptr ) {
    	LOG4CPLUS_ERROR(logger, "conext is nullptr" );
    } else if ( ac->err ) {
    	LOG4CPLUS_ERROR(logger, "Error: " << ac->errstr );
        return 1;
    }

    LOG4CPLUS_DEBUG(logger, "redisLibeventAttach" );
    redisLibeventAttach(ac,base);

    LOG4CPLUS_DEBUG(logger, "redisAsyncSetConnectCallback" );
    redisAsyncSetConnectCallback(ac,connectCallback);
    redisAsyncSetDisconnectCallback(ac,disconnectCallback);

    LOG4CPLUS_DEBUG(logger, "set" );
    redisAsyncCommand(ac, callback, NULL, "SET a/a.f32 %s", "1.1");
    redisAsyncCommand(ac, callback, NULL, "SET b/b.f32 %s", "2.2");

    LOG4CPLUS_DEBUG(logger, "get" );
    redisAsyncCommand(ac, callback, (char*)"end-1", "GET a/a.f32");

    LOG4CPLUS_DEBUG(logger, "get" );
    redisAsyncCommand(ac, callback, NULL, "GET b/b.f32");

//    for ( int i = 0; i<10; ++i ) {
//		LOG4CPLUS_DEBUG(logger, "mget" );
//		redisAsyncCommand(ac, callback, NULL, "MGET a/a.f32 b/b.f32");
//    }

    LOG4CPLUS_DEBUG(logger, "sub" );
    redisAsyncCommand(ac, callback, NULL, "subscribe c");

    LOG4CPLUS_DEBUG(logger, "event_base_dispatch" );
//    event_base_dispatch(base);

    try {
    	auto dispatch = [&](struct event_base *base){event_base_dispatch(base);};
    	auto future = std::async( std::launch::async, dispatch, base );

    	//...

    	this_thread::sleep_for( chrono::seconds(10) );
    	redisAsyncDisconnect(ac);

    	future_status status;
    	do {
			status = future.wait_for(chrono::seconds(1));
			if ( status == future_status::ready ) {
				future.get();
			} else if ( status == future_status::timeout ) {
				LOG4CPLUS_ERROR(logger, "timeout" );
			} else if ( status == future_status::deferred ) {
				LOG4CPLUS_ERROR(logger, "deferred" );
			}
    	} while( status != future_status::ready );
    } catch ( const exception& e ) {
    	LOG4CPLUS_ERROR(logger, e.what() );
    }
	cout << "---------------- end   program ------------" << endl;
	return 0;
}
