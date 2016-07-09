/*
 * temp.cpp
 *
 *  Created on: 2016. 6. 26.
 *      Author: juik
 */
#include <iostream>
#include "Point.h"

using namespace std;

template<typename T, typename U>
T sum( T a, U b ) {
	cout << __PRETTY_FUNCTION__ << "(" << a << "," << b << ")" << endl;
	T c = a + b;
	return c;
}

int main() {
	cout << sum(1,2) << endl;
	cout << sum(1.1,2.2) << endl;
	cout << sum(1.1,2) << endl;
	cout << sum('a',1) << endl;
	cout << sum(Point(1,1),Point(1,2)) << endl;

	cout << "---- end ----"  << endl;
}


