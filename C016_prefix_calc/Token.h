/*
 * Token.h
 *
 *  Created on: 2017. 11. 12.
 *      Author: cho
 */

#ifndef C016_PREFIX_CALC_TOKEN_H_
#define C016_PREFIX_CALC_TOKEN_H_

#include <iostream>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

enum class TokenType { OPERATOR, OPERAND, NONE };

class Token {
public:
	Token();
	Token(const std::string&);
	virtual ~Token();

	// member variables
	TokenType type = TokenType::NONE;
	char opr       = ' ';
	int  count     = 0;
	double opd     = 0.0f;

	// member function
	inline bool isOperator() const {
		return ( type == TokenType::OPERATOR );
	}

	inline bool isOperand() const {
		return ( type == TokenType::OPERAND );
	}

	bool isHigherOperator(const Token&);

	// member operators
	Token& operator=( const Token& );
	Token& operator+=( const Token& );
	Token& operator-=( const Token& );
	Token& operator*=( const Token& );
	Token& operator/=( const Token& );

//	Token& operator+=( const std::deque<Token>& );
//	Token& operator-=( const std::deque<Token>& );
//	Token& operator*=( const std::deque<Token>& );
//	Token& operator/=( const std::deque<Token>& );

	// constants
	static const std::string OPERATOR_RE;
	static const std::string OPERAND_RE;

	friend std::ostream& operator<<( std::ostream& os, const Token& t );
private:
	log4cplus::Logger _logger;
};

#endif /* C016_PREFIX_CALC_TOKEN_H_ */
