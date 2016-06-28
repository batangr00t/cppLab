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
	const int x;
	const int y;
	const double r;
public:
	Circle() : x(0), y(0), r(0.0) {
		cout << __PRETTY_FUNCTION__ << *this << endl;
	}

	Circle(int a, int b, double r) : x(a), y(b), r(r) {
		cout << __PRETTY_FUNCTION__ << *this << endl;
	}

	~Circle() {
		cout << __PRETTY_FUNCTION__ << *this << endl;
	}

	double getArea() {
		cout << __PRETTY_FUNCTION__ << *this << endl;
		return (PI * r * r );
	}

	friend ostream& operator<<( ostream& os, const Circle& c);
};

ostream& operator<<( ostream& os, const Circle& c) {
	os << &c << " (" << c.x << "," << c.y << ")(" << c.r << ")";
	return os;
}

class Sphere: public Circle {
protected:
	const int z;

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

	Sphere( int a, int b, int c, double r): Circle(a,b,r), z(c) {
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
		return (4.0/3.0 * PI * r * r* r);
	}

	friend ostream& operator<<( ostream& os, const Sphere& s );
};

ostream& operator<<( ostream& os, const Sphere& s ) {
	os << &s << " (" << s.x << "," << s.y << ","  << s.z << ")(" << s.r << ")";
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

