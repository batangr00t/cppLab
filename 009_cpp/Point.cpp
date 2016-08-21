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

Point::Point(): x(0), y(0) {
	cout << __PRETTY_FUNCTION__ << *this << endl;
}

Point::Point( int a, int b ): x(a), y(b) {
	cout << __PRETTY_FUNCTION__ << *this << endl;
}

Point::Point( const Point& p ) {
	x = p.x;
	y = p.y;
	cout << __PRETTY_FUNCTION__ << *this << endl;
}
Point::~Point() {
	cout << __PRETTY_FUNCTION__ << *this << endl;
};

double Point::norm() const {
	return sqrt( x * x + y * y );
}

Point Point::operator+( const Point& p ) {
	cout << *this << " + " << p << endl;
	return Point( x + p.x, y + p.y );
}

Point& Point::operator+=( const Point& p ) {
	cout << *this << " += " << p << endl;
	x += p.x;
	y += p.y;
	return *this;
}

ostream& operator<< (ostream& os, const Point& p ) {
	os << &p << "(" << p.x << ", " << p.y << ")";
	return os;
}


