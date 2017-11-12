/*
 * Token.cpp
 *
 *  Created on: 2017. 11. 12.
 *      Author: cho
 */

#include <regex>
#include "Token.h"

using namespace std;

const std::string Token::OPERATOR_RE = "[-+*/()]";
const std::string Token::OPERAND_RE = "([0-9]*\\.[0-9]+|[0-9]+)";

Token::Token(const string& n) : name( n ) {
	try {
		if ( regex_match( name, regex( OPERAND_RE ))) {
			value = stof( name );
		} else {
			value = 0.0f;
		}
	} catch( const exception& e ) {
		value = 0.0f;
		cout << "exception " << e.what() << endl;
	}
}

Token::~Token() {

}

std::ostream& operator<<( std::ostream& os, const Token& t ) {
	os << "{" << t.name << "," << t.value << "}";
	return os;
}
