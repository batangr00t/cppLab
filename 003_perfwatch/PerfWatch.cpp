/*
 * StopWatch.cpp
 *
 *  Created on: 2016. 4. 21.
 *      Author: juik
 */

#include <algorithm>
#include "PerfWatch.h"

PerfWatch::PerfWatch() : _count(0) {

}

PerfWatch::~PerfWatch() {

}

void PerfWatch::start() {
	_startTime = steady_clock::now();
}

void PerfWatch::stop() {
	steady_clock::time_point prev = _startTime;
	_lapList.reverse();
	_elapsedList.clear();
	for ( const auto & t : _lapList ) {
		_elapsedList.push_front(duration_cast<nanoseconds>(t - prev ));
	}
}

void PerfWatch::restart() {
	_lapList.clear();
	_elapsedList.clear();
	_count = 0;
	start();
}

long PerfWatch::min() {
	nanoseconds n = *min_element( _elapsedList.begin(), _elapsedList.end() );
	return n.count();
}

long PerfWatch::max() {
	nanoseconds n = *max_element( _elapsedList.begin(), _elapsedList.end() );
	return n.count();
}

int PerfWatch::count() {
	return _count;
}

void PerfWatch::lap() {
	_lapList.push_front( steady_clock::now() );
	_count++;
}


