/*
 * Token.h
 *
 *  Created on: 2017. 11. 12.
 *      Author: cho
 */

#ifndef C016_PREFIX_CALC_TOKEN_H_
#define C016_PREFIX_CALC_TOKEN_H_

#include <string>
#include <iostream>
#include <functional>

class Token {
public:
	Token(const std::string& n);
	virtual ~Token();
	const std::string name;
	float value;
	std::string type;

	static const std::string OPERATOR_RE;
	static const std::string OPERAND_RE;

	friend std::ostream& operator<<( std::ostream& os, const Token& t );
};

#endif /* C016_PREFIX_CALC_TOKEN_H_ */
