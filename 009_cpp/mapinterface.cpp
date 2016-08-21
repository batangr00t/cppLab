/*
 * val.cpp
 *
 *  Created on: 2016. 6. 27.
 *      Author: LG CNS
 */

#include <iostream>
#include <functional>
#include <memory>
#include <map>

using namespace std;

class Box {
public:
	Box():i(0) {
		cout << this << " : " << __PRETTY_FUNCTION__ << endl;
	}
	~Box() {
		cout << this << " : " << __PRETTY_FUNCTION__ << endl;
	}
	int i;
};

class A {
public:
	Box* pBox;
	int n;
};

int main() {
	cout << "------- start --- " << endl;

	Box box;



	map<string, A> m;

	A a = { &box, 32};
	A& ra = a;

	m.emplace( "aa", move(ra) );

	auto it = m.find("aa");
	cout << it->first << endl;
	cout << it->second.n << endl;

	cout << "------- end --- " << endl;
}

