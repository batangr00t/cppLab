/*
 * vector.cpp
 *
 *  Created on: 2016. 4. 24.
 *      Author: juik
 */
#include <vector>
#include <iostream>
#include <algorithm>

#include "Box.h"

using namespace std;

class MyVector {
public:
	void put( const Box& box ) {
		_vec.emplace_back( box );
	}

	Box& get() {
		Box& box = _vec.back();
		_vec.pop_back();
		return box;
	}

	void print() {
//		for ( const auto& b : _vec ) {
//			cout << b << ",";
//		}
		vector<Box>::iterator pos;
		for ( pos = _vec.begin(); pos != _vec.end(); pos++ ) {
			cout << *pos << ",";
		}

		cout << endl;
	}

private:
	vector<Box> _vec;
};

int main() {
	cout << "---------- start -----------------" << endl;

	MyVector vec;
	vec.print();
	cout << "--- 1" << endl;
	Box b(1);
	cout << "--- 2" << endl;
	vec.put( b );
	vec.put( Box(2) );
	cout << "--- 3" << endl;
	vec.print();
	cout << "--- 4" << endl;
	Box & b1 = vec.get();
	vec.print();
	cout << b1  << endl;

    cout << "--- 5" << endl;
	Box arr[3]= { Box("a"), Box("b"), Box("c") };
	vector<Box> toVec;
	copy_n( arr, 3, toVec.end());

	for ( const auto& e : toVec ) {
	    cout << e << endl;
	}

	cout << "----------  end  -----------------" << endl;
}
