/*
 * class2.cpp
 *
 *  Created on: 2016. 6. 28.
 *      Author: LG CNS
 */

#include <iostream>

using namespace std;

class A {
public:
	A(int n) : _a(n) {
		cout << "[" << this << "]" << __PRETTY_FUNCTION__ << _a << endl;
	}

	virtual ~A() {
		cout << "[" << this << "]" << __PRETTY_FUNCTION__ << _a << endl;
	}

private:
	int _a;
};

class B {
public:
	B(A& a): _mem(&a) {
		cout << "[" << this << "]" << __PRETTY_FUNCTION__ << endl;
	}

	virtual ~B() {
		cout << "[" << this << "]" << __PRETTY_FUNCTION__ << endl;
	}
private:
	A* _mem;
};

int main() {
	A a(1);

	B b(a);
}
