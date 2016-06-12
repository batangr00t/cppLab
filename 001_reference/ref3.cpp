/*
 * ref.cpp
 *
 *  Created on: 2016. 4. 13.
 *      Author: juik
 */

// for more infomation
// see http://en.cppreference.com/w/cpp/language/value_category

#include <iostream>
#include <vector>
#include "Box.h"

using namespace std;

int main() {
	cout << "\n====== start ==============================" << endl;

	cout << "\n1. push back =================" << endl;
	{
		vector<Box> vecBox;
		vecBox.reserve(4);
		cout << "-----push_back( Box(1) ) - " << endl;
		vecBox.push_back( Box(1) );    // create temorary object and destroy. and copy an object to heap
		cout << "-----push_back( Box(2) ) - " << endl;
		vecBox.push_back( Box(2) );
		cout << "-----push_back( Box(3) ) - " << endl;
		vecBox.push_back( Box(3) );
		cout << "-----push_back( Box(4) ) - " << endl;
		vecBox.push_back( Box(4) );
		cout << "-----after push_back( Box(4) ) - " << endl;
	}

	cout << "\n====== end ==============================" << endl;
	return 0;
} 	// destructor

