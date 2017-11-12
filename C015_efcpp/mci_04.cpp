/*
 * mci_01.cpp
 *
 *  Created on: 2017. 11. 11.
 *      Author: cho
 */
#include <iostream>
#include <typeinfo>
#include <vector>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

class Widget {};

template<typename T>
void f( const T& param ) {
	cout << "T     = " << type_id_with_cvr<T>().pretty_name() << endl;
	cout << "param = " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

vector<Widget> createVec() {return vector<Widget>{Widget()};};

int main() {
	cout << "---- start ----" << endl;

	const int theAnswer = 42;
	auto x = theAnswer;
	auto y = &theAnswer;

	cout << "=========== not recommend " << endl;
	cout << typeid(x).name() << endl;
	cout << typeid(x).name() << endl;

	cout << "=========== better " << endl;
	cout << type_id_with_cvr<decltype(x)>().pretty_name() << endl;
	cout << type_id_with_cvr<decltype(y)>().pretty_name() << endl;

	cout << "=========== good2 " << endl;
	const auto vw = createVec();
	if ( !vw.empty() ) {
		f(&vw[0]);
	}

	cout << "----  end  ----" << endl;
}


