/*
 * PrefixCalulator.cpp
 *
 *  Created on: 2017. 11. 12.
 *      Author: cho
 */

#include "PrefixCalculator.h"
using namespace std;

PrefixCalculator::PrefixCalculator() {
	// TODO Auto-generated constructor stub

}

PrefixCalculator::~PrefixCalculator() {
	// TODO Auto-generated destructor stub
}

void PrefixCalculator::eval(const Token& t) {
	if ( t.name == ")" ) {
		Token result = _calculate();
		_stack.pop_back(); // remove "(" TODO check "("
		_stack.emplace_back( result );
	} else {
		_stack.emplace_back( t );
	}

}

Token PrefixCalculator::_calculate() {
	// make parameters
	list<Token> params;
	for ( auto it = _stack.crbegin();
			   it != _stack.crend() && (*it).type == "OPERAND";
			   ++it ) {
		params.emplace_back( *it );
		_stack.pop_back();
	}
	params.reverse();

	Token op(_stack.back());
	_stack.pop_back();

	switch ( op.name[0] ) {
	case '+' :
		return add( params );
		break;
	case '-' :
		return subtract( params );
		break;
	case '*' :
		return multiply( params );
		break;
	case '/' :
		return divide( params );
		break;
	default:
		cout << "operator error " << op << endl;
		return Token("ERROR");
		break;
	}
}

Token PrefixCalculator::add( std::list<Token> params ) {
	float result = 0;
	for ( const auto& v : params ) {
		result += v.value;
	}

	return Token( to_string( result ));
}

Token PrefixCalculator::subtract( std::list<Token> params ) {
	float result = params.front().value;
	params.pop_front();

	for ( const auto& v : params ) {
		result -= v.value;
	}

	return Token( to_string( result ));
}

Token PrefixCalculator::multiply( std::list<Token> params ) {
	float result = params.front().value;
	params.pop_front();

	for ( const auto& v : params ) {
		result *= v.value;
	}

	return Token( to_string( result ));
}

Token PrefixCalculator::divide( std::list<Token> params ) {
	float result = params.front().value;
	params.pop_front();

	for ( const auto& v : params ) {
		result /= v.value;
	}

	return Token( to_string( result ));
}

std::ostream& operator<<( std::ostream& os, const PrefixCalculator& c ) {
	for ( const auto& e : c._stack ) {
		os << e;
	}
	return os;
}
