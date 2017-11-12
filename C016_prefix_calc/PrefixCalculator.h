/*
 * PrefixCalulator.h
 *
 *  Created on: 2017. 11. 12.
 *      Author: cho
 */

#ifndef C016_PREFIX_CALC_PREFIXCALCULATOR_H_
#define C016_PREFIX_CALC_PREFIXCALCULATOR_H_

#include <deque>
#include "Token.h"

class PrefixCalculator {
public:
	PrefixCalculator();
	virtual ~PrefixCalculator();

	void eval(const Token& t);

	friend std::ostream& operator<<( std::ostream& os, const PrefixCalculator& c );

private:
	std::deque<Token> _stack;
};

#endif /* C016_PREFIX_CALC_PREFIXCALCULATOR_H_ */
