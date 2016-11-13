/*
 * MessageQueue.cpp
 *
 *  Created on: 2016. 11. 13.
 *      Author: cho
 */

#include "MessageQueue.h"
#include "Log.h"

using namespace std;

template<typename T>
MessageQueue<T>::MessageQueue(unsigned int size) {
	Log::log( __PRETTY_FUNCTION__ );
	_q_max_size = size;
}

template<typename T>
MessageQueue<T>::~MessageQueue() {
	Log::log( __PRETTY_FUNCTION__ );
}

template<typename T>
void MessageQueue<T>::put(const T& val) {
	Log::log( __PRETTY_FUNCTION__ );
	unique_lock<mutex> ulk(_m);

	_cv_put.wait(ulk, [this]{ return _q.size() < _q_max_size;});
	Log::log( "_cv_put.wait return" );
	_q.push_back(val);
	_cv_get.notify_one();
	Log::log( "size = " + to_string(_q.size())  );
}

template<typename T>
void MessageQueue<T>::put(T&& val) {
	Log::log( __PRETTY_FUNCTION__ );
	unique_lock<mutex> ulk(_m);

	_cv_put.wait(ulk, [this]{ return _q.size() < _q_max_size;});
	Log::log( "_cv_put.wait return" );
	_q.push_back(val);
	_cv_get.notify_one();
	Log::log( "size = " + to_string(_q.size())  );
}

template<typename T>
T& MessageQueue<T>::get() {
	Log::log( __PRETTY_FUNCTION__ );
	unique_lock<mutex> ulk(_m);

	_cv_get.wait(ulk, [this]{ return !_q.empty();});
	Log::log( "_cv_get.wait return" );
	T& val = _q.front();
	_q.pop_front();
	_cv_put.notify_one();

	Log::log( "size = " + to_string(_q.size())  );

	return val;
}
