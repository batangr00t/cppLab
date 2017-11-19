/*
 * main.cpp
 *
 *  Created on: 2017. 11. 12.
 *      Author: cho
 */

#include <iostream>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include "Calculator.h"
#include "Token.h"

using namespace std;

static log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main"));

int main() {
	cout << "---- start ----" << endl;
	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");

	Calculator calc;
	cout << " CalMode is " << calc.mode << endl;

	for ( string line; getline( cin, line); ) {
		if ( line == "prefix") {
			calc.mode = CalMode::PREFIX;
		} else if ( line == "infix" ) {
			calc.mode = CalMode::INFIX;
		} else if ( line == "postfix" ) {
			calc.mode = CalMode::POSTFIX;
		} else {
			double result = calc.eval( line );
			cout << "================== result : " << result << endl;
			calc.reset();
		}
		cout << " CalMode is " << calc.mode << endl;
	}

	cout << "----  end  ----" << endl;
}

