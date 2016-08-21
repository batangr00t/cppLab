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

	//
	cout << "2. emplace_back -------------" << endl;
	vector<Box> vec2;
	vec2.reserve(4);
	vec2.emplace_back( Box(1) );
	vec2.emplace_back( Box(2) );
	vec2.emplace_back( Box(3) );
	vec2.emplace_back( Box(4) );

	cout << "3. emplace_back -------------" << endl;
	vector<Box> vec3;
	vec3.reserve(4);
	vec3.emplace_back( 1 );
	vec3.emplace_back( 2 );
	vec3.emplace_back( 3 );
	vec3.emplace_back( 4 );

	cout << "4. copy -------------" << endl;
	cout << "4.1 vec4 생성 -------------" << endl;
	vector<Box> vec4;
	vec4.emplace_back( 1 );
	vec4.emplace_back( 2 );
	vec4.emplace_back( 3 );
	vec4.emplace_back( 4 );
	cout << "4.2 vec5 = vec4  -------------" << endl;
	vector<Box> vec5 = vec4;
	cout << "4.3 vec4 = vec5  -------------" << endl;
	vec4 = vec5;
	cout << "4.3 --------------" << endl;
	for ( const Box& b : vec4 ) {
		cout << b << endl;
	}

	for ( const Box& b : vec5 ) {
			cout << b << endl;
		}

	cout << "----------  end  -----------------" << endl;
}
