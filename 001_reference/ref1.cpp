/*
 * ref.cpp
 *
 *  Created on: 2016. 4. 13.
 *      Author: juik
 */

#include <iostream>
#include <functional>
#include <list>

#include "../001_reference/Box.h"

using namespace std;

int main() {
	cout << "====== start ==============================" << endl;
	cout << "----create Box objects " << endl;
	Box aBox("a");         // constuctor
	Box bBox("b");         // constuctor
	Box cBox = aBox;       // copy constuctor
	Box &dBox = bBox;      // does not create an object. good!

	cout << "\n----create a list and push objects to this list" << endl;
	list<Box> boxList;
	boxList.push_back( aBox );  // copy constuctor
	boxList.push_back( bBox );  // copy constuctor
	boxList.push_back( cBox );  // copy constuctor
	boxList.push_back( dBox );  // copy constuctor

	cout << "\n----traverse a list " << endl;
	for ( const Box b : boxList ) {  // temporary objects, cons/dest
		cout << b << endl;
	}

	cout << "\n----traverse a list using ref " << endl;
	for ( const Box &b : boxList ) {  // good!. does not create any object.
		cout << b << endl;
	}

	cout << "\n----pop_front box" << endl;
	while ( !boxList.empty()) {
		boxList.pop_front();           // destructor
	}

	cout << "\n====== end   ==============================" << endl;
	return 0;
} 	// destructor

