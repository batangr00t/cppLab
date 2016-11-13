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

using namespace std;

void f(vector<double>& v, double* res) {
	cout << __PRETTY_FUNCTION__ << endl;
	double sum = 0;
	for ( auto e : v ) {
		sum += e;
		cout << "f(" << e << ") Hello. sum = " << sum << endl;
	}

	if ( res != nullptr ) {
		*res = sum;
	}
}

struct F {
	void operator()() {
		cout << "Parallel world" << endl;
	}
};

struct G {
public:
	G(vector<double>& v, double* res ) : _v(v), _res(res) {
		cout << __PRETTY_FUNCTION__ << endl;
	}

	~G() {
		cout << __PRETTY_FUNCTION__ << endl;
	}

	void operator()() {
		cout << __PRETTY_FUNCTION__ << endl;
		double sum = 0;
		for ( auto e : _v) {
			sum += e;
			cout << "F(" << e << ") Parallel World. sum = " << sum << endl;
		}
		if ( _res != nullptr ) {
			*_res = sum;
		}
	}
private:
	vector<double>& _v;
	double * _res = nullptr;
};

int main() {
	vector<double> some_vec { 1, 2, 3, 4, 5, 6, 7, 8, 9};
	vector<double> vec2 { 10, 11, 12, 13, 14, 15};

	// result
	double res1;
	double res3;

	thread t1{f, ref(some_vec), &res1};
	F objectF{};
	thread t2{objectF};
	thread t3{G{vec2, &res3}};

	t1.join();
	t2.join();
	t3.join();

	cout << "res1 = " << res1 << endl;
	cout << "res3 = " << res3 << endl;
}
