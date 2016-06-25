/*
 * value.cpp
 *
 *  Created on: 2016. 6. 12.
 *      Author: juik
 */
#include <iostream>

using namespace std;

int main() {
	int a;
	int b;
	int c;

	( ++a ) = 100;
	( a += b ) = 200;
	( a ? b : c) = 100;
	"Hello, World" = 'c';

	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl;

}


