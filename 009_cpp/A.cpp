#include <iostream>
#include <sstream>

#include "A.h"
using namespace std;

A::~A() {
	cout << __PRETTY_FUNCTION__ << endl;
}

A::A() : size(0) {
	cout << __PRETTY_FUNCTION__ << endl;
}

std::ostream& operator<< ( std::ostream& os, const A &binstr ) {
	return os;
}
