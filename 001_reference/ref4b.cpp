/*
 * ref.cpp
 *
 *  Created on: 2016. 4. 13.
 *      Author: juik
 */

// this is a sample program with memory leak

#include <iostream>
#include <vector>
#include "Box.h"

using namespace std;

int main() {
	cout << "\n====== start ==============================" << endl;

	cout << "\n1. ===========================" << endl;
	{
		vector<Box*> vecBox;
		cout << "-----before push_back( Box(1) ) - " << endl;
		vecBox.push_back( new Box(1) );
		cout << "-----before push_back( Box(2) ) - " << endl;
		vecBox.push_back( new Box(2) );
		cout << "-----before push_back( Box(3) ) - " << endl;
		vecBox.push_back( new Box(3) );
		cout << "-----before push_back( Box(4) ) - " << endl;
		vecBox.push_back( new Box(4) );
		cout << "-----after push_back( Box(4) ) - " << endl;
	}

	cout << "\n====== end ==============================" << endl;
	return 0;
} 	// destructor

