/*
 * List.h
 *
 *  Created on: 2017. 10. 8.
 *      Author: cho
 */

#ifndef C014_CATEGORY_LIST_H_
#define C014_CATEGORY_LIST_H_

#include <cassert>

template<class T>
class List {
	struct Item {
		Item(T v, Item const * tail) : _val(v), _next(tail) {};
		T _val;
		Item const * _next;
	};
public:
	List() : _head(nullptr) {}
	List(T v, List tail) : _head( new Item(v, tail._head)) {}
	virtual ~List() {}
	bool isEmpty() const { return !_head; }
	T front() const {
		assert(!isEmpty());
		return _head->_val;
	}
	List pop_front() const {
		assert(!isEmpty());
		return List(_head->_next);
	}
	List push_front(T v) const {
		return List(v, *this);
	}
private:
	Item const * _head;

};

#endif /* C014_CATEGORY_LIST_H_ */
