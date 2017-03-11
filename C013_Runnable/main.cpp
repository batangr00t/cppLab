/*
 * main.cpp
 *
 *  Created on: 2016. 12. 4.
 *      Author: cho
 */
#include <iostream>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>

#include "SampleRunnable.h"

using namespace std;

static log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main"));

int main() {
	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");

	LOG4CPLUS_INFO( logger, "====== start =========" );
	SampleRunnable aSvr{"a"};
	SampleRunnable bSvr{"b"};

	// make thread
	aSvr.init();
	bSvr.init();

	// get state
	cout << aSvr.getState() << endl;
	cout << bSvr.getState() << endl;

	// start a main logic but stop b
	aSvr.start();
	bSvr.stop();

	// stop ar
	aSvr.stop();

	LOG4CPLUS_INFO( logger, "====== end =========" );
}


