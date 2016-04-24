/*
 * vector.cpp
 *
 *  Created on: 2016. 4. 24.
 *      Author: juik
 */
#include <vector>
#include <iostream>
#include "Box.h"

using namespace std;

int main() {
	cout << "---------- start -----------------" << endl;
	cout << "1. push_back -------------" << endl;
	vector<Box> vec1;
	vec1.reserve(4);
	vec1.push_back( Box(1) );
	vec1.push_back( Box(2) );
	vec1.push_back( Box(3) );
	vec1.push_back( Box(4) );

	cout << "2. emplace_back -------------" << endl;
	vector<Box> vec2;
	vec2.reserve(4);
	vec2.emplace_back( Box(1) );
	vec2.emplace_back( Box(2) );
	vec2.emplace_back( Box(3) );
	vec2.emplace_back( Box(4) );

	cout << "----------  end  -----------------" << endl;
}
