/*
 * PrefixCalulator.cpp
 *
 *  Created on: 2017. 11. 12.
 *      Author: cho
 */

#include "PrefixCalculator.h"

PrefixCalculator::PrefixCalculator() {
	// TODO Auto-generated constructor stub

}

PrefixCalculator::~PrefixCalculator() {
	// TODO Auto-generated destructor stub
}

void PrefixCalculator::eval(const Token& t) {
	_stack.push_back( t );
}

std::ostream& operator<<( std::ostream& os, const PrefixCalculator& c ) {
	for ( const auto& e : c._stack ) {
		os << e;
	}
	return os;
}
