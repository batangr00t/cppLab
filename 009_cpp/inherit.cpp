/*
 * inherit.cpp
 *
 *  Created on: 2016. 6. 26.
 *      Author: juik
 */

#include <iostream>
using namespace std;

#define PI 3.14

class Circle {
protected :
	const int _x;
	const int _y;
	const double _r;
public:
	Circle() : _x(0), _y(0), _r(0.0) {
		cout << __PRETTY_FUNCTION__ << *this << endl;
	}

	Circle(int a, int b, double r) : _x(a), _y(b), _r(r) {
		cout << __PRETTY_FUNCTION__ << *this << endl;
	}

	~Circle() {
		cout << __PRETTY_FUNCTION__ << *this << endl;
	}

	double getArea() {
		cout << __PRETTY_FUNCTION__ << *this << endl;
		return (PI * _r * _r );
	}

	friend ostream& operator<<( ostream& os, const Circle& c);
};

ostream& operator<<( ostream& os, const Circle& c) {
	os << &c << " (" << c._x << "," << c._y << ")(" << c._r << ")";
	return os;
}

class Sphere: public Circle {
protected:
	const int _z;

public:
//	Sphere( int a, int b, int c, double r) {
//		x = a;
//		y = b;
//		z = c;
//		this->r = r;
//		cout << __PRETTY_FUNCTION__ << *this << endl;
//	}

//	Sphere( int a, int b, int c, double r):  x(a), y(b), z(c), r(r) {
//		cout << __PRETTY_FUNCTION__ << *this << endl;
//	}

	Sphere( int a, int b, int c, double r): Circle(a,b,r), _z(c) {
		cout << __PRETTY_FUNCTION__ << *this << endl;
	}

	~Sphere() {
		cout << __PRETTY_FUNCTION__ << *this << endl;
	}

	double getArea() {
		cout << __PRETTY_FUNCTION__ << *this << endl;
		return (4.0 * Circle::getArea());
	}

	double getVolume() {
		return (4.0/3.0 * PI * _r * _r * _r);
	}

	friend ostream& operator<<( ostream& os, const Sphere& s );
};

ostream& operator<<( ostream& os, const Sphere& s ) {
	os << &s << " (" << s._x << "," << s._y << ","  << s._z << ")(" << s._r << ")";
	return os;
}

int main() {

	Circle c( 1, 1, 1);
	cout << "area = " << c.getArea() << endl;

	Sphere s( 1, 1, 1, 1);
	cout << "surface area = " << s.getArea() << endl;
	cout << "valume = " << s.getVolume() << endl;
	cout << "area = " << s.Circle::getArea() << endl;

	cout << "----ref--" << endl;
	Circle c2 = Sphere(0,0,0,1);
	cout << "area? = " << c2.getArea() << endl;
	cout << "----pointer--" << endl;
	Circle * cp = new Sphere(0,0,0,1);
	cout << "area? = " << cp->getArea() << endl;
	delete cp;

	cout << "end ------" << endl;
}

