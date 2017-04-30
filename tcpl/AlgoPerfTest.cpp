/*
 * AlgoPerfTest.cpp
 *
 *  Created on: 2017. 4. 30.
 *      Author: cho
 */

#include <boost/timer/timer.hpp>
#include <boost/algorithm/clamp.hpp>
#include <iostream>

using namespace std;

int main() {

	int count = 1000*1000;

	// min max
	cout << "--- Minimum/maximum operations" << endl;
	cout << "------ clamp() " << count << endl;
	{
		boost::timer::cpu_timer timer;
		timer.start();
		for ( int i = 0; i< count; ++i ) {
			boost::algorithm::clamp(i, 10.0, 20.0 );
		}

		timer.stop();
		cout << "clamp() : " << timer.format() << endl;
	}
	return 0;
}


