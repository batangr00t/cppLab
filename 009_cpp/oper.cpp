/*
 * oper.cpp
 *
 *  Created on: 2016. 6. 25.
 *      Author: juik
 */
#include <iostream>

using namespace std;

class Point {
private:
	int x;
	int y;

public:
	Point(): x(0), y(0) {
		cout << __PRETTY_FUNCTION__ << " (" << x << ", " << y << ")" << endl;
	}

	Point( int a, int b ): x(a), y(b) {
		cout << __PRETTY_FUNCTION__ << " (" << x << ", " << y << ")" << endl;
	}

	~Point() {
		cout << __PRETTY_FUNCTION__ << " (" << x << ", " << y << ")" << endl;
	};

	Point sum( const Point &p ) {
		x += p.x;
		y += p.y;
		return *this;
		//return Point( x + p.x, y + p.y );
	}

	Point operator+( const Point& p ) {
		cout << *this << " + " << p << endl;
		return Point( x + p.x, y + p.y );
	}

	Point& operator+=( const Point& p ) {
		cout << *this << " += " << p << endl;
		x += p.x;
		y += p.y;
		return *this;
	}

	void print() {
		cout << "(" << x << ", " << y << ")" << endl;
	}

	friend ostream& operator<< (ostream& os, const Point& p );

};

ostream& operator<< (ostream& os, const Point& p ) {
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}

int main() {
	cout << " -------- start " << endl;
	Point p0(0,0);
	Point p1(1,1);
	Point p2(2,2);
	Point p3;
	Point p4;

	cout << " -------- + " << endl;
	p3 = p0 + p1 + p2;
	cout << "p3 = " << p3 << endl;

	cout << " -------- += " << endl;
	p4 += p1 += p2 += p3;
	//p4 += p2;
	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;
	cout << "p3 = " << p3 << endl;
	cout << "p4 = " << p4 << endl;

	cout << " -------- end " << endl;

}


