/*
 * main.cpp
 *
 *  Created on: 2017. 11. 12.
 *      Author: cho
 */

#include <iostream>
#include "Calculator.h"
#include "Token.h"

using namespace std;

int main() {
	cout << "---- start ----" << endl;

	Calculator calc;

	for ( string line; getline( cin, line); ) {
		double result = calc.eval( line );
		cout << "================== result : " << result << endl;
		calc.reset();
	}

	cout << "----  end  ----" << endl;
}

