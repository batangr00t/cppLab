/*
 * Calculator.h
 *
 *  Created on: 2017. 11. 15.
 *      Author: cho
 */

#ifndef C016_CALCULATOR_CALCULATOR_H_
#define C016_CALCULATOR_CALCULATOR_H_

#include <deque>
#include <list>
#include <regex>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "../c016_calculator/Token.h"

enum class CalMode { PREFIX, INFIX, POSTFIX };
std::ostream& operator<<( std::ostream& os, const CalMode& c);

class Calculator {
public:
	CalMode mode = CalMode::PREFIX;

	Calculator();
	virtual ~Calculator();
	double eval(const std::string& expr);
	void reset();
	friend std::ostream& operator<<( std::ostream& os, const Calculator& c );

private:
	log4cplus::Logger _logger;

	// raw input
	std::string _line;

	// token list
	std::deque<Token> _operators;
	std::deque<Token> _tokens;  // postfix
	std::deque<Token> _result;
	std::regex _token_re;

	// tokenize : expr => _tokens  without '(', ')'
	void _prefixTokenize(const std::string& expr);  // prefix  expr => postfix token
	void _infixTokenize(const std::string& expr);   // infix   expr => postfix token
	void _postfixTokenize(const std::string& expr); // postfix expr => postfix token

	// calculator : _tokens => _result
	void _postfixCalc();      // postfix => result

	// compute using parameter in the result
	Token _postfixCompute( const Token& opr );

};

#endif /* C016_CALCULATOR_CALCULATOR_H_ */
