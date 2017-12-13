/*
 * ActiveObject.h
 *
 *  Created on: 2017. 12. 13.
 *      Author: cho
 */

#ifndef C013_ACTIVE_OBJECT_ACTIVEOBJECT_H_
#define C013_ACTIVE_OBJECT_ACTIVEOBJECT_H_

#include <log4cplus/loggingmacros.h>
#include <future>
#include <atomic>

// The active object is the object which has a thread
// The thread is created when an active object is constructed and terminated on destruction.

class ActiveObject {
public:
	enum class State {
		CREATED, INITIALIZING, READY, RUNNING, FINALIZING, STOPPED, MAX
	};
	friend std::ostream& operator<<( std::ostream& os, const ActiveObject::State& state );

public:
	ActiveObject(const std::string& name);
	virtual ~ActiveObject();

	// thread main function
	// --------------------------------------------------------------------------------
	//        init()                     start()      stop()
	//          |                          |            |
	//          v                          v            v
	// created ---> initializing -> ready ---> running ---> finalizing -> stopped
	//                   |            |          |              ^
	//                   |            |          |              |
	//                   +------------+----------+--------------+
	//                                   stop()
	// --------------------------------------------------------------------------------

	// control method
	void init();     // execute doInitialize() and wait start
	void start();    // execute doRun() which is the main loop
	void stop();     // execute doFinalize() and stop thread

	// mission method
	virtual bool doInitilize() = 0;
	virtual bool doRun() = 0;
	virtual bool doFinalize() = 0;

	// monitoring
	State getState() const;

	// operator overloading
	friend std::ostream& operator<<( std::ostream& os, const ActiveObject& object );

protected:
	// main loop
	void _main();

	// logger
	log4cplus::Logger _logger;

	// active object name
	std::string _name;

	// active object state
	std::atomic<State> _state;

	// mail loop result
	std::future<void> _main_loop_result;

};

#endif /* C013_ACTIVE_OBJECT_ACTIVEOBJECT_H_ */
