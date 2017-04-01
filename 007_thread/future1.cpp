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

void thFun( promise<string> && prms ) {
	try {
		string msg = "Hello from future";
		cout << "msg in thFun : " << (void*)msg.data() << endl;
		throw runtime_error("exception from future!");
		prms.set_value(msg);
	} catch (...) {
		prms.set_exception( std::current_exception());
	}
}

int main() {
	cout << "start -------" << endl;

	promise<string> prms;
	future<string> ftr = prms.get_future();
	thread th(&thFun, move(prms));
	try {
		string msg = ftr.get();
		cout << msg << endl;
		cout << "msg : " << (void*)msg.data() << endl;
	} catch( const exception &e ) {
		cout << e.what() << endl;
	}
	th.join();

	cout << "end  -------" << endl;
}


