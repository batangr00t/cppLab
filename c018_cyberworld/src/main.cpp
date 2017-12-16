#include <iostream>
#include <thread>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include "World.h"
#include "Screen.h"
#include "Define.h"

using namespace std;

int main() {
	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main"));

	LOG4CPLUS_INFO( logger, "===== start ");
	Screen screen;
	screen.showTitle();
	{
		// create the world
		auto size = screen.getSize();
		World& world = World::getInstance();
		PointBuilderRandom builder{size.second/4.0, size.first/4.0};
		world.generatePoints(builder, 100);

		// show the world
		for ( int i = 0; i<(Hz*30); ++i ) {
			this_thread::sleep_for( chrono::milliseconds(1000/Hz) );
			screen.showWorld();
		}
	}
	screen.showEnding();

	// terminate the world
	LOG4CPLUS_INFO( logger, "===== end " );


    return 0;
}
