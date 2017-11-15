/*
 * Calculator.cpp
 *
 *  Created on: 2017. 11. 15.
 *      Author: cho
 */

#include <cmath>
#include "Calculator.h"
using namespace std;

Calculator::Calculator() :
	_token_re( Token::OPERATOR_RE + "|" + Token::OPERAND_RE) {
	cerr << __LINE__ << __PRETTY_FUNCTION__ << endl;
}

Calculator::~Calculator() {
	cerr << __LINE__ << __PRETTY_FUNCTION__ << endl;
}

double Calculator::eval(const std::string& expr) {
	double result;

	_tokenize( expr );
	_prefixCalcRight();

	if ( _result.size() == 1 ) {
		Token token = _result.front();
		if ( token.type == TokenType::OPERAND ) {
			result = token.opd;
		} else {
			cerr << __LINE__ << __PRETTY_FUNCTION__ << " result is not OPERAND" << endl;
			result = nan("");
		}
	} else {
		cerr << __LINE__ << __PRETTY_FUNCTION__ << " result stack's size is not one" << endl;
		result = nan("");
	}

	return result;
}

void Calculator::reset() {
	_tokens.clear();
	_result.clear();
}

// tokenize : expr => _tokens
void Calculator::_tokenize(const std::string& expr) {
	cout << __LINE__ << __PRETTY_FUNCTION__ << endl;

	// clean tokens
	_tokens.clear();

	// tokenize
	for ( auto b = sregex_token_iterator( expr.begin(), expr.end(), _token_re );
	      b!=sregex_token_iterator();
	      b++ ) {
		_tokens.push_back( Token(*b) );
		cout << *this << endl;
	}
}

// prefix calculator : _tokens => _result
void Calculator::_prefixCalcRight() {
	cout << __LINE__ << __PRETTY_FUNCTION__ << endl;

	for ( auto it = _tokens.crbegin(); it != _tokens.crend(); ++it ) {
		if ( it->type == TokenType::OPERATOR ) {
			switch( it->opr ) {
			case ')' :
				_result.push_front( *it );
				break;
			case '(':
				// skip
				break;
			default: // compute
				_result.push_front( _compute( *it ) );
				break;
			}
		} else if ( it->type == TokenType::OPERAND ) {
			_result.push_front( *it );
		}
		cout << *this << endl;
	}
}

void Calculator::_prefixCalcLeft() {

}

Token Calculator::_compute( const Token& oprToken ) {
	cout << __LINE__ << __PRETTY_FUNCTION__ << endl;

	if ( _result.empty() ) {
		cerr << "incomplete expr : _result are empty";
		return Token();
	}

	deque<Token> params;
	auto& param = _result.front();
	while ( param.opr != ')' && !_result.empty() ) {
		params.push_back( param );
		_result.pop_front();
		param = _result.front();
		cout << *this << endl;
	}
	if ( !_result.empty() ) _result.pop_front(); // remove ')'

	if ( params.size() < 2 ) {
		cerr << "incomplete expr : params are empty or one";
		return Token();
	}

	Token computed = params.front();
	cout << "computed = " << computed << endl;
	params.pop_front();

	switch ( oprToken.opr ) {
	case '+' : for ( const auto& p : params ) computed += p; break;
	case '-' : for ( const auto& p : params ) computed -= p; break;
	case '*' : for ( const auto& p : params ) computed *= p; break;
	case '/' : for ( const auto& p : params ) computed /= p; break;
	default  : computed = Token(); break;
	}

	return computed;
}

std::ostream& operator<<( std::ostream& os, const Calculator& c ) {
	os << " _tokens : ";
	for ( const auto& e : c._tokens ) {
		os << e;
	}
	os << endl;
	os << " _result : ";
	for ( const auto& e : c._result ) {
		os << e;
	}
	return os;
}
