/*
 * Token.h
 *
 *  Created on: 2017. 11. 12.
 *      Author: cho
 */

#ifndef C016_PREFIX_CALC_TOKEN_H_
#define C016_PREFIX_CALC_TOKEN_H_

#include <iostream>

enum class TokenType { OPERATOR, OPERAND, NONE };

class Token {
public:
	Token();
	Token(const std::string&);
	virtual ~Token();

	// member variables
	TokenType type = TokenType::NONE;
	char opr       = ' ';
	double opd     = 0.0f;

	// member operators
	Token& operator=( const Token& );
	Token& operator+=( const Token& );
	Token& operator-=( const Token& );
	Token& operator*=( const Token& );
	Token& operator/=( const Token& );

	// constants
	static const std::string OPERATOR_RE;
	static const std::string OPERAND_RE;

	friend std::ostream& operator<<( std::ostream& os, const Token& t );
};

#endif /* C016_PREFIX_CALC_TOKEN_H_ */
