/*
 * PerfWatch.h
 *
 *  Created on: 2016. 4. 21.
 *      Author: juik
 */

#ifndef CPPLAB_PERFWATCH_H_
#define CPPLAB_PERFWATCH_H_

#include <forward_list>
#include <chrono>

using namespace std;
using namespace std::chrono;

class PerfWatch {
public:
	PerfWatch();
	virtual ~PerfWatch();
	void start();
	void stop();
	void restart();
	long min();
	long max();
	int count();
	void lap();
	void histogram();
private:
	steady_clock::time_point _startTime;
	forward_list<steady_clock::time_point> _lapList;
	forward_list<nanoseconds> _elapsedList;
	size_t _count;
};

#endif /* CPPLAB_PERFWATCH_H_ */
