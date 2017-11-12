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
			type = "OPERAND";
		} else {
			value = 0.0f;
			type = "OPERATOR";
		}
	} catch( const exception& e ) {
		value = 0.0f;
		type = "ERROR";
		cout << "exception " << e.what() << endl;
	}
}

Token::~Token() {

}

std::ostream& operator<<( std::ostream& os, const Token& t ) {
	if ( t.type == "OPERATOR") {
		os << "{" << t.name << "}";
	} else if ( t.type == "OPERAND") {
		os << "{" << t.value << "}";
	} else {
		os << "{ERROR}";
	}
	return os;
}
