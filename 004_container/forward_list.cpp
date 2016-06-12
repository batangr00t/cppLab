/*
 * foward_list.cpp
 *
 *  Created on: 2016. 4. 24.
 *      Author: juik
 */
#include <forward_list>
#include <algorithm>
#include <iostream>
#include "Box.h"
using namespace std;

int main() {
	cout << "---------- start -----------------" << endl;
	cout << "1. forward_list  ----------" << endl;
	forward_list<int> fl;

	fl.push_front(1);
	fl.push_front(2);
	fl.push_front(3);
	fl.push_front(4);

	cout << "2. travel for  ----------" << endl;
	for ( const auto & i : fl ) {
		cout << i << ", ";
	}
	cout << endl;

	cout << "2. travel with interator  ----------" << endl;
	for ( auto it = fl.begin(); it != fl.end(); it++ ) {
			cout << *it << ", ";
	}
	cout << endl;

	cout << "3. travel after reverse ----------" << endl;
	fl.reverse();
	for ( const auto & i : fl ) {
		cout << i << ", ";
	}
	cout << endl;

	cout << "4. find min  ----------" << endl;
	auto pair = minmax_element( fl.begin(), fl.end() );
	cout << "min: " << *pair.first << ", max:" << *pair.second  << endl;

	cout << "5. forward_list  box ----------" << endl;
	{
		forward_list<Box> flb;

		flb.push_front(Box(1));
		flb.push_front(Box(2));
		flb.push_front(Box(3));
		flb.push_front(Box(4));
		flb.push_front(Box(5));
	}

	cout << "----------  end  -----------------" << endl;
}
