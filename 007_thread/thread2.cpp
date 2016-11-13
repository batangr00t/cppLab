/*
 * thread1.cpp
 *
 *  form "The C++ Programming Language 4th Edition"
 *
 *  Created on: 2016. 5. 31.
 *      Author: juik
 */

#include <thread>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
void task() {
	cout << "hi" << endl;
}

int main() {
	vector<thread> mythreads;

	for ( int i=0; i < 3; ++i ) {
		mythreads.emplace_back( thread{task} );
	}

	for ( auto& e : mythreads ) {
		e.join();
	}

}
