/*
 * constex.cpp
 *
 *  Created on: 2017. 10. 8.
 *      Author: cho
 */

#include <iostream>

using namespace std;

int main() {

	int int_variableA = 0;
	int int_variableB = 9;

	cout << "int_variableA = " << int_variableA << endl;
	cout << "int_variableB = " << int_variableB << endl;

	const int * p1 = &int_variableA;
	//*p1 = 1; // 	error: assignment of read-only location ‘* p’
	cout << "*p1 = " << *p1 << endl;
	p1 = &int_variableB;
	cout << "*p1 = " << *p1 << endl;

	int const * p2 = &int_variableA;
	//*p2 = 2; // error: assignment of read-only location ‘* p2’
	cout << "*p2 = " << *p2 << endl;
	p2 = &int_variableB;
	cout << "*p2 = " << *p2 << endl;

	int * const p3 = &int_variableA;
	*p3 = 3;
	cout << "*p3 = " << *p3 << endl;
	//p3 = &int_variableB; // error: assignment of read-only variable ‘p3’
	cout << "*p3 = " << *p3 << endl;
}

