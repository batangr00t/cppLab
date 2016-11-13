#include <iostream>
#include <exception>
#include "Vector.h"

using namespace std;

Vector f( Vector &x, Vector& y ) {
	cout << __PRETTY_FUNCTION__ << endl;

	Vector r;

	r = x + y;

	return r;
}

int main() {
	cout << "START ------------------ " << endl;

	Vector v{1,2,3,4,5};
	Vector v1{v};
	Vector v2;

	v2 = v1;

	cout << "v   = " << v << endl;
	cout << "v1  = " << v1 << endl;
	cout << "v2  = " << v2 << endl;

	cout << "------------------ " << endl;
	cout << "v1 + v2 = " <<  f(v1, v2) << endl;

	cout << "END   ------------------ " << endl;

	return 0;
}



