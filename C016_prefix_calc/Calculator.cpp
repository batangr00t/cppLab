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
	_logger( log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Calculator"))),
	_token_re( Token::OPERATOR_RE + "|" + Token::OPERAND_RE) {
	LOG4CPLUS_DEBUG( _logger, __PRETTY_FUNCTION__ );
}

Calculator::~Calculator() {
	LOG4CPLUS_DEBUG( _logger, __PRETTY_FUNCTION__ );
}

double Calculator::eval(const std::string& expr) {
	LOG4CPLUS_DEBUG( _logger, __PRETTY_FUNCTION__ );

	// copy input string
	_line = expr;

	// parse and compute
	switch( mode ) {
	case CalMode::PREFIX:  _prefixTokenize( expr );	 break;
	case CalMode::INFIX:   _infixTokenize( expr );	 break;
	case CalMode::POSTFIX: _postfixTokenize( expr ); break;
	}
	_postfixCalc();

	// check result
	double result;
	if ( _result.size() == 1 ) {
		Token token = _result.front();
		if ( token.isOperand() ) {
			result = token.opd;
		} else {
			LOG4CPLUS_ERROR( _logger, "result is not OPERAND");
			result = nan("");
		}
	} else {
		LOG4CPLUS_ERROR( _logger, "result stack's size is not one" );
		result = nan("");
	}

	return result;
}

void Calculator::reset() {
	LOG4CPLUS_DEBUG( _logger, __PRETTY_FUNCTION__ );

	_operators.clear();
	_tokens.clear();
	_result.clear();
}

//prefix  expr => postfix token without '(', ')'
void Calculator::_prefixTokenize(const std::string& expr) {
	LOG4CPLUS_DEBUG( _logger, __PRETTY_FUNCTION__ );

	// clean tokens
	_tokens.clear();

	// tokenize
	for ( auto it = sregex_token_iterator( expr.begin(), expr.end(), _token_re );
	      it != sregex_token_iterator();
	      ++it ) {
		Token token(*it);
		if ( token.opr == '(' ) {
			//skip
		} else if ( token.opr == ')' ) {
			_operators.pop_back();
			if ( !_operators.empty() && ++(_operators.back().count) > 1 ) {
				_tokens.push_back( _operators.back() );
			}
		} else if ( token.isOperator() ) {
			_operators.push_back( token );
		} else { // operand
			_tokens.push_back( token );
			if ( !_operators.empty() ) {
				_operators.back().count++;
				if ( _operators.back().count > 1 ) {
					_tokens.push_back( _operators.back() );
				}
			}
		}

		LOG4CPLUS_INFO( _logger, *this );
	}
}

//infix  expr => postfix token without '(', ')'
void Calculator::_infixTokenize(const std::string& expr) {
	LOG4CPLUS_DEBUG( _logger, __PRETTY_FUNCTION__ );

	// clean tokens
	_tokens.clear();

	// tokenize
	for ( auto it = sregex_token_iterator( expr.begin(), expr.end(), _token_re );
	      it!=sregex_token_iterator();
	      it++ ) {
		Token token(*it);
		if ( token.opr == '(' ) {
			_operators.push_back( token );
		} else if ( token.opr == ')' ) {
			while ( !_operators.empty() && _operators.back().opr != '(' ) {
				_tokens.push_back( _operators.back() );
				_operators.pop_back();
			}
			_operators.pop_back();
		} else if ( token.isOperator() ) {
			while ( !_operators.empty() && _operators.back().opr != '(' &&
					_operators.back().isHigherOperator(token) ) {
				_tokens.push_back( _operators.back() );
				_operators.pop_back();
			}
			_operators.push_back( token );
		} else { // operand
			_tokens.push_back( token );
		}
		LOG4CPLUS_INFO( _logger, *this );
	}

	// push left operators
	while ( !_operators.empty() ) {
		_tokens.push_back( _operators.back() );
		_operators.pop_back();
	}
}

//postfix  expr => postfix token without '(', ')'
void Calculator::_postfixTokenize(const std::string& expr) {
	LOG4CPLUS_DEBUG( _logger, __PRETTY_FUNCTION__ );

	// clean tokens
	_tokens.clear();

	// tokenize
	for ( auto it = sregex_token_iterator( expr.begin(), expr.end(), _token_re );
	      it!=sregex_token_iterator();
	      it++ ) {
		Token token(*it);
		if ( token.opr == '(' ) {
			//skip
		} else if ( token.opr == ')' ) {
			//skip
		} else { // operand
			_tokens.push_back( token );
		}
		LOG4CPLUS_INFO( _logger, *this );
	}
}

// postfix calculator : _tokens => _result, calculate from begin to end
void Calculator::_postfixCalc() {
	LOG4CPLUS_DEBUG( _logger, __PRETTY_FUNCTION__ );

	LOG4CPLUS_INFO( _logger, *this );
	for ( auto it = _tokens.cbegin(); it != _tokens.cend(); ++it ) {
		if ( it->isOperator() ) {
			_result.push_back( _postfixCompute( *it ) );
		} else if ( it->isOperand() ) {
			_result.push_back( *it );
		}
		_tokens.pop_front();
		LOG4CPLUS_INFO( _logger, *this );
	}
}

// first pop rhs
Token Calculator::_postfixCompute( const Token& oprToken ) {
	LOG4CPLUS_DEBUG( _logger, __PRETTY_FUNCTION__ );
	Token lhs;
	Token rhs;

	// rhs
	if ( _result.empty() ) {
		LOG4CPLUS_ERROR( _logger, "incomplete expr : _result are empty");
		return Token();
	} else {
		rhs = _result.back();
		_result.pop_back();
	}

	// lhs
	if ( _result.empty() ) {
		LOG4CPLUS_ERROR( _logger, "incomplete expr : _result are empty");
		return Token();
	} else {
		lhs = _result.back();
		_result.pop_back();
	}

	switch ( oprToken.opr ) {
	case '+' : lhs += rhs; break;
	case '-' : lhs -= rhs; break;
	case '*' : lhs *= rhs; break;
	case '/' : lhs /= rhs; break;
	default  : lhs = Token(); break;
	}

	return lhs;
}

std::ostream& operator<<( std::ostream& os, const CalMode& c) {
	switch( c ) {
	case CalMode::PREFIX:  os << "PREFIX";  break;
	case CalMode::INFIX:   os << "INFIX";   break;
	case CalMode::POSTFIX: os << "POSTFIX"; break;
	}

	return os;
}

std::ostream& operator<<( std::ostream& os, const Calculator& c ) {
	os << endl;
	os << "CalMode   : " << c.mode << endl;
	os << "input line: \"" << c._line << "\"" << endl;
	os << "operTokens: |";
	for ( const auto& e : c._operators ) {
		os << e;
	}
	os << "|" << endl;
	os << "tokens    : |";
	for ( const auto& e : c._tokens ) {
		os << e;
	}
	os << "|" << endl;
	os << "result    : |";
	for ( const auto& e : c._result ) {
		os << e;
	}
	os << "|";
	return os;
}
