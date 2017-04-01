/*
 * main.cpp
 *
 *  Created on: 2017. 3. 25.
 *      Author: cho
 */

#include <iostream>
#include <future>
#include <thread>
#include <string>

using namespace std;

string fun() {
	string str("Hello from fun");
	throw overflow_error("exception from fun");
	return str;
}

int main() {
	cout << "start -------" << endl;

	future<string> ftr = std::async( launch::async, &fun);
	cout << "Hello from main" << endl;
	try {
		string str = ftr.get();
		cout << str << endl;
	} catch ( const exception& e ) {
		cout << e.what() << endl;
	}
	cout << "end  -------" << endl;
}


