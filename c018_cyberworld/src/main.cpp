#include <iostream>
#include <thread>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include "World.h"

using namespace std;

int main() {
	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main"));

	LOG4CPLUS_INFO( logger, "===== start ");

	World& world = World::getInstance();
	PointBuilderRandom builder;
	world.generatePoints(builder, 50);

	for ( int i = 0; i<20; ++i ) {
		cout << world << endl;
		this_thread::sleep_for( chrono::milliseconds(1000));
		world.move();
	}

	LOG4CPLUS_INFO( logger, "===== end " );
    return 0;
}
