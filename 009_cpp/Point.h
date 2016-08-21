/*
 * oper.cpp
 *
 *  Created on: 2016. 6. 25.
 *      Author: juik
 */
#include <iostream>

class Point {
private:
	int x;
	int y;

public:
	Point();
	Point( int a, int b );
	Point( const Point& );
	~Point();
	double norm() const;
	Point operator+( const Point& p );
	Point& operator+=( const Point& p );
	friend std::ostream& operator<< (std::ostream& os, const Point& p );
};
