/*
 * cons.cpp
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
	Point( int a = 0, int b= 0 ): x(a), y(b) {
		clog << __PRETTY_FUNCTION__ << " (" << x << ", " << y << ")" << endl;
	}

	virtual ~Point() {
		clog << __PRETTY_FUNCTION__ << " (" << x << ", " << y << ")" << endl;
	}

};

class Circle {
public:
	int radius;
	Point center;
};

int main() {
	Circle c1{};
	Circle c2 = c1;
	clog << c2.radius << endl;

	Circle c3{0,0};
	clog << c3.radius << endl;
}


