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

	// thread를 생성한 다음에 move 함
	cout << "case 1 --------------" << endl;
	for ( int i=0; i < 3; ++i ) {
		thread th{task};
		// mythreads.push_back( th );  compile error
		mythreads.push_back( move(th) );
	}

	for ( auto& e : mythreads ) {
		e.join();
	}

	// case 1,
	// 생성 후 move 하지 않고 바로 저장하기 때문에 더 선호되는 방식
	// case 1 에서 terminate 된 thread도 남아 있음
	// terminated 된 thread는 joinable하지 않음
	cout << "case 2 -------------" << endl;
	for ( int i=0; i < 3; ++i ) {
		mythreads.emplace_back(task);
	}

	for ( auto& e : mythreads ) {
		cout << e.get_id() << endl;
		if ( e.joinable() ) e.join();
	}

	cout << "case 3 -------------" << endl;
	mythreads.clear();
	for (int i = 0; i < 3; ++i) {
		mythreads.emplace_back(task);
	}

	for (auto& e : mythreads) {
		cout << e.get_id() << endl;
		if (e.joinable())
			e.join();
	}

}
