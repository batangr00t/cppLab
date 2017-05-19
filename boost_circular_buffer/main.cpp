/*
 * main.cpp
 *
 *  Created on: 2017. 5. 19.
 *      Author: cho
 */

#include <iostream>
#include <boost/circular_buffer.hpp>
#include <boost/timer/timer.hpp>

using namespace std;

int main() {

	cout << "====== BEGIN ========" << endl;

	boost::timer::auto_cpu_timer t(1);
	boost::circular_buffer<double> cb;
	cb.set_capacity(5);

	for ( int i = 0; i<24*60*60; i++ ) cb.push_back( i );

	cout << "=== for ( double e : cb ) {" << endl;
	for ( double e : cb ) {
		cout << e << ", ";
	}
	cout << endl;

	cout << "=== cb.begin()++; for ( double e : cb ) {" << endl;
	cb.begin()++;
	for ( double e : cb ) {
		cout << e << ", ";
	}
	cout << endl;

	cout << "=== for ( auto it = cb.begin()++; it != cb.end(); it++ ) {" << endl;
	for ( auto it = cb.begin()++; it != cb.end(); it++ ) {
		cout << *it << ", ";
	}
	cout << endl;

	cout << "=== for ( auto it = ++cb.begin(); it != cb.end(); it++ ) {" << endl;
	for ( auto it = ++cb.begin(); it != cb.end(); it++ ) {
		cout << *it << ", ";
	}
	cout << endl;

	cout << "=== for ( auto it = cb.begin()+1; it != cb.end(); it++ ) {" << endl;
	for ( auto it = cb.begin()+1; it != cb.end(); it++ ) {
		cout << *it << ", ";
	}
	cout << endl;

	cout << "====== END ========" << endl;
	return 0;
}


