#include <iostream>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include "World.h"

int main() {
	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main"));

	LOG4CPLUS_INFO( logger, "===== start ");

	World& world = World::getInstance();

	world.add_point(10);
	LOG4CPLUS_INFO( logger, world );

	LOG4CPLUS_INFO( logger, "===== end " );
    return 0;
}
