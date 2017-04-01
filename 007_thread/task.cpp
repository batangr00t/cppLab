/*
 * task.cpp
 *
 *  Created on: 2017. 3. 26.
 *      Author: cho
 */
#include <iostream>
#include <vector>
#include <future>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

int main()
{
	cout << "start --------- " << endl;
	cout << "Main thread id : " << this_thread::get_id() << endl;

	vector<future<void>> futures;
	for ( int i=0; i<10; ++i ) {
		auto fut = async([] {
				this_thread::sleep_for( chrono::seconds(2));
				cout << this_thread::get_id() << endl;
		});
		futures.push_back( move(fut) );
	}
	cout << "end async call   --------- " << endl;

	for_each( futures.begin(), futures.end(), [](future<void>& fut)
	{
		fut.wait();
		cout << "end of wait  --------- " << endl;
	});


	this_thread::sleep_for( chrono::seconds(10));

	cout << "end   --------- " << endl;
}


