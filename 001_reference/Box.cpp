/*
 * Box.cpp
 *
 *  Created on: 2016. 4. 13.
 *      Author: juik
 */
#include "../001_reference/Box.h"

Box::Box() : Box("anonymous") {
	cout << __PRETTY_FUNCTION__ << " = " << *this << endl;
}

Box::Box(const string& name) {
	_name = name;
	cout << __PRETTY_FUNCTION__ << " = " << *this << endl;
}

Box::Box(const Box & b) {
	_name = b._name;
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

ostream& operator<< ( ostream& os, const Box &b ) {
	os << &b << ":Box(\"" << b._name << "\")";

	return os;
}
