/*
 * PrimeNumber.h
 *
 *  Created on: 2016. 5. 21.
 *      Author: juik
 */

#ifndef PRIME_PRIMENUMBER_H_
#define PRIME_PRIMENUMBER_H_

#include <list>

class PrimeNumber {
public:
	PrimeNumber();
	virtual ~PrimeNumber();
	unsigned long long at( std::list<unsigned long long>::size_type nth);
private:
	std::list<unsigned long long> _primes;
	bool add_if_prime(unsigned long long);

};

#endif /* PRIME_PRIMENUMBER_H_ */
