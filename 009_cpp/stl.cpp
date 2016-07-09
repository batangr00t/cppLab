/*
 * stl.cpp
 *
 *  Created on: 2016. 6. 26.
 *      Author: juik
 */

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "Point.h"

using namespace std;

void norm( const Point& p ) {
	//cout << __PRETTY_FUNCTION__ << endl;
	cout << p.norm() << endl;
}

int main() {
	cout << "---- start ----" << endl;
	vector<Point> intV;
	//intV.reserve(65);

	cout << "---- push_back ----" << endl;
	for ( int i=0; i<4; i++ ) {
		intV.emplace_back(i,i);
	}

	cout << "---- print ----" << endl;
	for ( const Point& p : intV ) {
		cout << p << ", ";
	}
	cout << endl;

	cout << "---- for_each ----" << endl;
	for_each( intV.begin(), intV.end(), norm);

	cout << "---- rotate ----" << endl;
	rotate( intV.begin(), intV.begin() + 1, intV.end());

	cout << "---- print ----" << endl;
	for ( const Point& p : intV ) {
		cout << p << ", ";
	}
	cout << endl;

	cout << "---- end ----" << endl;

}


