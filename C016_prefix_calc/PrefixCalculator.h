/*
 * PrefixCalulator.h
 *
 *  Created on: 2017. 11. 12.
 *      Author: cho
 */

#ifndef C016_PREFIX_CALC_PREFIXCALCULATOR_H_
#define C016_PREFIX_CALC_PREFIXCALCULATOR_H_

#include <deque>
#include <list>
#include "Token.h"

class PrefixCalculator {
public:
	PrefixCalculator();
	virtual ~PrefixCalculator();

	void eval(const Token& t);

	friend std::ostream& operator<<( std::ostream& os, const PrefixCalculator& c );

	Token add( std::list<Token> params );
	Token subtract( std::list<Token> params );
	Token multiply( std::list<Token> params );
	Token divide( std::list<Token> params );
private:
	std::deque<Token> _stack;
	Token _calculate();
};

#endif /* C016_PREFIX_CALC_PREFIXCALCULATOR_H_ */
