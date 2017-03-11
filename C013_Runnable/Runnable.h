/*
 * Runnable.h
 *
 *  Created on: 2016. 12. 4.
 *      Author: cho
 */

#ifndef C013_RUNNABLE_RUNNABLE_H_
#define C013_RUNNABLE_RUNNABLE_H_

#include <log4cplus/loggingmacros.h>

class Runnable {
public:
	Runnable();
	virtual ~Runnable();

	// thread main function
	//
	//     init()                        start()     stop()
	//       |                              |          |
	//    O  -> initializing -> initialized -> running -> stopped
	//                |              |            |         ^
	//                +--------------+------------+---------+
	//                            stop()

	// control method
	void init();     // initialize
	void start();    // start main loop
	void stop();     // stop thread

	// mission method
	virtual bool doInitilize() = 0;
	virtual bool doRun() = 0;
	virtual bool doFinalize() = 0;

	// monitoring method just for debug
	std::string getState();

protected:
	log4cplus::Logger _logger;

private:
	void _main();           // called in constructor
	void _waitStart();
};

#endif /* C013_RUNNABLE_RUNNABLE_H_ */
