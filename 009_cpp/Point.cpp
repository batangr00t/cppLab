/*
 * oper.cpp
 *
 *  Created on: 2016. 6. 25.
 *      Author: juik
 */
#include <iostream>
#include <cmath>
#include "Point.h"

using namespace std;

Point::Point(): _x(0), _y(0) {
	cout << __PRETTY_FUNCTION__ << *this << endl;
}

Point::Point( int a, int b ): _x(a), _y(b) {
	cout << __PRETTY_FUNCTION__ << *this << endl;
}

Point::Point( const Point& p ) {
	_x = p._x;
	_y = p._y;
	cout << __PRETTY_FUNCTION__ << *this << endl;
}
Point::~Point() {
	cout << __PRETTY_FUNCTION__ << *this << endl;
};

double Point::norm() const {
	return sqrt( _x * _x + _y * _y );
}

Point Point::operator+( const Point& p ) {
	cout << *this << " + " << p << endl;
	return Point( _x + p._x, _y + p._y );
}

Point& Point::operator+=( const Point& p ) {
	cout << *this << " += " << p << endl;
	_x += p._x;
	_y += p._y;
	return *this;
}

ostream& operator<< (ostream& os, const Point& p ) {
	os << &p << "(" << p._x << ", " << p._y << ")";
	return os;
}


