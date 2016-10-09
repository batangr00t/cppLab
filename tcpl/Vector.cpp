/*
 * Vector.cpp
 *
 *  Created on: 2016. 10. 9.
 *      Author: cho
 */

#include <iostream>
#include "Vector.h"

using namespace std;

// constructor
Vector::Vector(): elem{nullptr}, sz{0} {
	cout << __PRETTY_FUNCTION__ << *this << endl;
}

Vector::Vector(int s): elem{new double[s]}, sz{s} {
	cout << __PRETTY_FUNCTION__ << *this << endl;
}

Vector::Vector(std::initializer_list<double> lst)
	: elem{new double[lst.size()]},
	  sz{static_cast<int>(lst.size())} {
	copy(lst.begin(), lst.end(), elem);
	cout << __PRETTY_FUNCTION__ << *this << endl;
}

// destructor
Vector::~Vector() {
	cout << __PRETTY_FUNCTION__ << *this << endl;
	if ( elem != nullptr ) delete[] elem;
}

// copy constructor
Vector::Vector(const Vector& v): elem{new double[v.sz]}, sz{v.sz} {
	// Copies the elements in the range, defined by [first, last)
	//      first   , pass-the-end
	copy( &v.elem[0], &v.elem[sz], elem);
	cout << __PRETTY_FUNCTION__ << *this << endl;
}

// copy assignment
Vector& Vector::operator=(const Vector& v) {
	cout << __PRETTY_FUNCTION__ << *this << endl;

	// delete old array
	if ( elem != nullptr ) delete[] elem;

	// set new array
	sz = v.sz;
	elem = new double[sz];

	// copy contents
	for ( int i=0; i<sz; ++i ) {
		elem[i] = v.elem[i];
	}

	return *this;
}

double& Vector::operator[](int i) {
	//cout << __PRETTY_FUNCTION__ << *this << endl;
	return elem[i];
}

const double& Vector::operator[](int i) const {
	//cout << __PRETTY_FUNCTION__ << *this << endl;
	return elem[i];
}

int Vector::size() const {
	return sz;
}

// print contents of Vector
std::ostream& operator<<( std::ostream& os, const Vector& v) {
	os << " [" << hex << ((v.sz == 0 )?0:v.elem) << "] -> elem[" << dec << v.sz << "]{";
	for ( int i = 0; i<v.sz; ++i ) {
		os << v.elem[i] << "|";
	}
	os << "}";
	return os;
}