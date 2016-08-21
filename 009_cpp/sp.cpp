/*
 * sp.cpp
 *
 *  Created on: 2016. 6. 29.
 *      Author: LG CNS
 */
#include <iostream>
#include <memory>

using namespace std;

class A {
private:
	int x;
	int y;
public:
	A(int a):x(a), y(a) {
		cout << __PRETTY_FUNCTION__ << endl;
	}
	~A() {
		cout << __PRETTY_FUNCTION__ << endl;
	}
	void print() {
		cout << "(" << x << "," << y << ")" << endl;
	}
};

void func( shared_ptr<A> spA ) {
	spA->print();
	cout << "count = " << spA.use_count() << endl;
}

int main() {
	A a(1);
	shared_ptr<A> sp1(&a);
	cout << "count = " << sp1.use_count() << endl;
	func( sp1 );
	cout << "count = " << sp1.use_count() << endl;

	shared_ptr<A> sp2(sp1);
	func( sp2 );

}



