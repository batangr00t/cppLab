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

Token::Token() {
	cerr << __LINE__ << __PRETTY_FUNCTION__ << endl;
}

Token::Token(const string& str) {
	cerr << __LINE__ << __PRETTY_FUNCTION__ << endl;
	try {
		if ( regex_match( str, regex( OPERATOR_RE ))) {
			opr = str[0];
			type = TokenType::OPERATOR;
		} else if ( regex_match( str, regex( OPERAND_RE ) ) ) {
			opd = stof( str );
			type = TokenType::OPERAND;
		}
	} catch( const exception& e ) {
		cout << "exception " << e.what() << endl;
	}
}

Token::~Token() {
	cerr << __LINE__ << __PRETTY_FUNCTION__ << endl;
}

Token& Token::operator=(const Token& other) {
	opr = other.opr;
	opd = other.opd;
	type = other.type;

	return *this;
}

Token& Token::operator+=( const Token& t ) {
	if ( type == TokenType::OPERAND && t.type == TokenType::OPERAND ) {
		opd += t.opd;
	} else {
		type = TokenType::NONE;
		cerr << __LINE__ << __PRETTY_FUNCTION__ << " : not OPERAND" << endl;
	}

	return *this;
}

Token& Token::operator-=( const Token& t ) {
	if ( type == TokenType::OPERAND && t.type == TokenType::OPERAND ) {
		opd -= t.opd;
	} else {
		type = TokenType::NONE;
		cerr << __LINE__ << __PRETTY_FUNCTION__ << " : not OPERAND" << endl;
	}

	return *this;
}

Token& Token::operator*=( const Token& t ) {
	if ( type == TokenType::OPERAND && t.type == TokenType::OPERAND ) {
		opd *= t.opd;
	} else {
		type = TokenType::NONE;
		cerr << __LINE__ << __PRETTY_FUNCTION__ << " : not OPERAND" << endl;
	}

	return *this;
}

Token& Token::operator/=( const Token& t ) {
	if ( type == TokenType::OPERAND && t.type == TokenType::OPERAND ) {
		opd /= t.opd;
	} else {
		type = TokenType::NONE;
		cerr << __LINE__ << __PRETTY_FUNCTION__ << " : not OPERAND" << endl;
	}

	return *this;
}

std::ostream& operator<<( std::ostream& os, const Token& t ) {
	if ( t.type == TokenType::OPERATOR) {
		os << "{" << t.opr << "}";
	} else if ( t.type == TokenType::OPERAND) {
		os << "{" << t.opd << "}";
	} else {
		os << "{NONE}";
	}
	return os;
}
