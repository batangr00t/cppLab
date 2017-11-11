/*
 * mci_01.cpp
 *
 *  Created on: 2017. 11. 11.
 *      Author: cho
 */
#include <iostream>
#include <typeinfo>

using namespace std;

template<typename T>
void f1( T& param) {
	cout << __PRETTY_FUNCTION__ << " : " << typeid(param).name() << endl;
}

template<typename T>
void f2( const T& param) {
	cout << __PRETTY_FUNCTION__ << " : " << typeid(param).name() << endl;
}

int main() {
	cout << "---- start ----" << endl;

	// case 1: ParamType = pointer or reference but not universal reference
	{
		int x = 0;
		const int cx = x;
		const int& rx = x;
		f1(x);
		f1(cx);
		f1(rx);
		f2(x);
		f2(cx);
		f2(rx);
	}

	cout << "----  end  ----" << endl;
}


