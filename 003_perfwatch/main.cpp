/*
 * main.cpp
 *
 *  Created on: 2016. 4. 21.
 *      Author: juik
 */

#include <iostream>
#include <cmath>
#include "PerfWatch.h"

using namespace std;

void func( int n ) {
	for(int i=0; i<n*10; i++) {
		double d = cos(i) * sin(i) * cos(i*1.2) * sin(i*2.122432432);
	}
}

int main(int argc, char *argv[]) {
	cout << "---------------- start program ------------" << endl;

	PerfWatch time;
	time.start();
	for ( int i=0; i<100; i++ ) {
		func(i);
		time.lap();
	}
	time.stop();

	cout << "count:" << time.count() << endl;
	cout << "min:" << time.min()/1000.0 << " micro seconds" << endl;
	cout << "max:" << time.max()/1000.0 << " micro seconds" << endl;



	cout << "---------------- end    program ------------" << endl;
	return 0;
}
