/*
 * mutex.cpp
 *
 *  Created on: 2016. 11. 12.
 *      Author: cho
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <unistd.h>

using namespace std;

mutex total_mutex;
double total = 0;

void hello(vector<double>& v) {
	total_mutex.lock();
	for ( auto e : v ) {
		total += e;
		cout << "total = " << total << endl;
	}
	total_mutex.unlock();
}

int main() {

	cout << "thread::hardware_concurrency() = " << thread::hardware_concurrency() << endl;
	cout << "main thread = " << hex << this_thread::get_id() << endl;

	vector<double> vec{1,2,3,4,5,6,7,8,9,10};

	thread th0;
	thread th1{hello, ref(vec)};
	thread th2{hello, ref(vec)};

	th1.join();
	th2.join();
}

