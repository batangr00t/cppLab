/*
 * regex.cpp
 *
 *  Created on: 2017. 11. 12.
 *      Author: cho
 */

#include <iostream>
#include <regex>

using namespace std;

int main() {
	cout << "---- start ----" << endl;

	regex ws_re("\\s+"); // whitespace
	regex token("[-()+*/]|[0-9]+");
	auto rend = sregex_token_iterator();

	for ( string line; getline( cin, line); ) {
		{
			auto b = sregex_token_iterator( line.begin(), line.end(), ws_re, -1 );
			while (b!=rend) std::cout << "[" << *b++ << "] ";
			cout << endl;
		}

		for ( auto b = sregex_token_iterator( line.begin(), line.end(), token );
		      b!=sregex_token_iterator();
		      b++) {
			std::cout << "[" << *b << "] ";
		}
		cout << endl;
	}

	cout << "----  end  ----" << endl;
}



