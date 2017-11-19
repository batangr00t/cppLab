/*
 * Token.cpp
 *
 *  Created on: 2017. 11. 12.
 *      Author: cho
 */

#include "../c016_calculator/Token.h"

#include <regex>

using namespace std;

const std::string Token::OPERATOR_RE = "[-+*/()]";
const std::string Token::OPERAND_RE = "([0-9]*\\.[0-9]+|[0-9]+)";

Token::Token() :
	_logger(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Token"))) {
	LOG4CPLUS_DEBUG( _logger, __PRETTY_FUNCTION__ );
}

Token::Token(const string& str) :
	_logger(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Token"))) {

	LOG4CPLUS_DEBUG( _logger, __PRETTY_FUNCTION__ );
	try {
		if ( regex_match( str, regex( OPERATOR_RE ))) {
			opr = str[0];
			type = TokenType::OPERATOR;
		} else if ( regex_match( str, regex( OPERAND_RE ) ) ) {
			opd = stof( str );
			type = TokenType::OPERAND;
		}
	} catch( const exception& e ) {
		LOG4CPLUS_ERROR( _logger, "exception " << e.what() );
	}
}

Token::~Token() {
	LOG4CPLUS_DEBUG( _logger, __PRETTY_FUNCTION__ );
}

bool Token::isHigherOperator(const Token& other ) {
	bool result = false;

	switch( opr ) {
	case '*':
	case '/':
		if ( other.opr == '+' or other.opr == '-' ) result = true;
		break;
	default:
		result = false;
		break;
	}

	return result;
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
		LOG4CPLUS_ERROR( _logger, "not OPERAND");
	}

	return *this;
}

Token& Token::operator-=( const Token& t ) {
	if ( type == TokenType::OPERAND && t.type == TokenType::OPERAND ) {
		opd -= t.opd;
	} else {
		type = TokenType::NONE;
		LOG4CPLUS_ERROR( _logger, "not OPERAND");
	}

	return *this;
}

Token& Token::operator*=( const Token& t ) {
	if ( type == TokenType::OPERAND && t.type == TokenType::OPERAND ) {
		opd *= t.opd;
	} else {
		type = TokenType::NONE;
		LOG4CPLUS_ERROR( _logger, "not OPERAND");
	}

	return *this;
}

Token& Token::operator/=( const Token& t ) {
	if ( type == TokenType::OPERAND && t.type == TokenType::OPERAND ) {
		opd /= t.opd;
	} else {
		type = TokenType::NONE;
		LOG4CPLUS_ERROR( _logger, "not OPERAND");
	}

	return *this;
}

//Token& Token::operator+=( const std::deque<Token>& params ) {
//	for ( const auto& p : params ) *this += p;
//	return *this;
//}
//
//Token& Token::operator-=( const std::deque<Token>& params ) {
//	for ( const auto& p : params ) *this -= p;
//	return *this;
//}
//
//Token& Token::operator*=( const std::deque<Token>& params ) {
//	for ( const auto& p : params ) *this *= p;
//	return *this;
//}
//
//Token& Token::operator/=( const std::deque<Token>& params ) {
//	for ( const auto& p : params ) *this /= p;
//	return *this;
//}

std::ostream& operator<<( std::ostream& os, const Token& t ) {
	if ( t.type == TokenType::OPERATOR) {
		os << "{" << t.opr << "," << t.count << "}";
	} else if ( t.type == TokenType::OPERAND) {
		os << "{" << t.opd << "}";
	} else {
		os << "{NONE}";
	}
	return os;
}
