/*
 * MessageQueue.h
 *
 *  Created on: 2016. 11. 13.
 *      Author: cho
 */

#ifndef _THREAD_MESSAGEQUEUE_H_
#define _THREAD_MESSAGEQUEUE_H_

#include <mutex>
#include <list>
#include <condition_variable>

template<typename T>
class MessageQueue {
public:
	MessageQueue(unsigned int size = 10);
	virtual ~MessageQueue();

	void put(const T& val);
	void put(T&& val);
	T& get();

private:
	std::mutex _m;
	std::condition_variable _cv_put;
	std::condition_variable _cv_get;
	std::list<T> _q;
	unsigned int _q_max_size;
};

#include "MessageQueue.cpp"

#endif /* _THREAD_MESSAGEQUEUE_H_ */
