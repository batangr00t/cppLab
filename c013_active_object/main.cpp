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

#include "Sample.h"
using namespace std;

int main() {
	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main"));

	LOG4CPLUS_INFO( logger, "====== start =========" );
	Sample sample("sample");
	this_thread::sleep_for( chrono::seconds(1));

	sample.init();
	this_thread::sleep_for( chrono::seconds(1));

	sample.start();
	this_thread::sleep_for( chrono::seconds(1));

	sample.stop();
	this_thread::sleep_for( chrono::seconds(1));

	LOG4CPLUS_INFO( logger, "====== end =========" );
}


