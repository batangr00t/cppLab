/*
 * main.cpp
 *
 *  Created on: 2017. 11. 12.
 *      Author: cho
 */

#include <iostream>
#include <regex>
#include "PrefixCalculator.h"
#include "Token.h"

using namespace std;

int main() {
	cout << "---- start ----" << endl;

	PrefixCalculator calc;

	regex token_re("[-+*/()]|" + Token::OPERAND_RE);
	auto rend = sregex_token_iterator();

	for ( string line; getline( cin, line); ) {
		for ( auto b = sregex_token_iterator( line.begin(), line.end(), token_re );
		      b!=sregex_token_iterator();
		      b++ ) {
			Token token(*b);
			std::cout << token;
			calc.eval( token );

		}
		cout << endl;
		cout << calc << endl;
	}

	cout << "----  end  ----" << endl;
}

