/*
 * Calculator.h
 *
 *  Created on: 2017. 11. 15.
 *      Author: cho
 */

#ifndef C016_PREFIX_CALC_CALCULATOR_H_
#define C016_PREFIX_CALC_CALCULATOR_H_

#include <deque>
#include <list>
#include <regex>
#include "Token.h"

class Calculator {
public:
	Calculator();
	virtual ~Calculator();

	double eval(const std::string& expr);

	// clean deques
	void reset();

	friend std::ostream& operator<<( std::ostream& os, const Calculator& c );

private:
	// token list
	std::deque<Token> _tokens;
	std::deque<Token> _result;
	std::regex _token_re;

	// tokenize : expr => _tokens
	void _tokenize(const std::string& expr);

	// prefix calculator : _tokens => _result
	void _prefixCalcRight();
	void _prefixCalcLeft();

	// compute using parameter in the result
	Token _compute( const Token& opr );

};

#endif /* C016_PREFIX_CALC_CALCULATOR_H_ */
