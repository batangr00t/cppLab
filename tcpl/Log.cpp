/*
 * Log.cpp
 *
 *  Created on: 2016. 11. 13.
 *      Author: cho
 */

#include <iostream>
#include "Log.h"

using namespace std;

mutex Log::_m{};

void Log::log(const std::string& msg) {
	lock_guard<mutex> lk(_m);
	cout << msg << endl;
}
