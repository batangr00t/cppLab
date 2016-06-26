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
	Point( int a = 0, int b= 0 ): x(a), y(b) {
		cout << __PRETTY_FUNCTION__ << " (" << x << ", " << y << ")" << endl;
	}

};

class Circle {
	int radius;
	Point center;
};

int main() {
	Circle c1;
	Circle c2 = c1;
}


