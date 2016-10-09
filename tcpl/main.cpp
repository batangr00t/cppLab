#include <iostream>
#include <exception>
#include "Vector.h"

using namespace std;
Vector operator+( const Vector& a, const Vector& b ) {
	cout << __PRETTY_FUNCTION__ << endl;

	if ( a.size() != b.size() ) throw exception{};

	Vector res(a.size());

	for ( int i=0; i<a.size(); ++i ) {
		res[i] = a[i] + b[i];
	}

	return res;

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

	cout << "v1 + v2 = " <<  v1+v2 << endl;

	cout << "END   ------------------ " << endl;

	return 0;
}



