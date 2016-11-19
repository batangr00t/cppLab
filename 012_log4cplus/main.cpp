#include <iostream>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>

using namespace std;

log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main"));

int main(int argc, char *argv[]) {
	int count = 1;
	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");

	LOG4CPLUS_INFO( logger, "-------- start ---------------");
	if ( argc > 1 ) count = atoi( argv[1] );
	for ( int i = 0; i<count; ++i ) {
		LOG4CPLUS_INFO( logger, "-----" << i << "---------------");
	}
	LOG4CPLUS_INFO( logger, "-------- end   ---------------");
	return 0;
}
