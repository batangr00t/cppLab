/*
 * Box.cpp
 *
 *  Created on: 2016. 4. 13.
 *      Author: juik
 */
#include <string>
#include "Box.h"

int Box::seq = 0;

Box::Box() {
	_id = ++Box::seq;
	_name = to_string(_id);
	cout << __PRETTY_FUNCTION__ << " = " << *this << endl;
}

Box::Box(const Box & b) {
	_name = b._name;
	_id = b._id;
	cout << __PRETTY_FUNCTION__ << " = " << *this << endl;
}

Box::Box(const Box && b) {
	_name = b._name;
	_id = b._id;
	cout << __PRETTY_FUNCTION__ << " = " << *this << endl;
}

Box::Box(const string& name) {
	_name = name;
	_id = ++Box::seq;
	cout << __PRETTY_FUNCTION__ << " = " << *this << endl;
}

Box::Box(int id ) {
	_id = id;
	//_name = to_string(_id);
	cout << __PRETTY_FUNCTION__ << " = " << *this << endl;
}

Box::~Box() {
	cout << __PRETTY_FUNCTION__ << " = " << *this << endl;
}

const string& Box::getName() {
	return _name;
}

void Box::setName(const string& name) {
	_name = name;
}

void Box::operator=(const Box& b) {
	_name = b._name;
	_id = b._id;
	cout << __PRETTY_FUNCTION__ << " = " << *this << endl;
}
ostream& operator<< ( ostream& os, const Box &b ) {
	os << "Box(" << b._id << ",\"" << b._name << "\") : " << &b ;

	return os;
}
