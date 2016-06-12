/*
 * PrimeNumber.cpp
 *
 *  Created on: 2016. 5. 21.
 *      Author: juik
 */

#include "PrimeNumber.h"
#include <iostream>

PrimeNumber::PrimeNumber() {
	_primes.push_back(2);
	_primes.push_back(3);
}

PrimeNumber::~PrimeNumber() {
	// TODO Auto-generated destructor stub
}

unsigned long long PrimeNumber::at(
		std::list<unsigned long long>::size_type nth) {
	std::list<unsigned long long>::size_type current_size = _primes.size();
	unsigned long long found_prime;

	if ( nth > current_size ) {
		unsigned long long dedicated_prime = _primes.back() + 2;

		for (auto i = current_size+1; i <= nth; i++) {
			while ( !add_if_prime(dedicated_prime) ) {
				dedicated_prime += 2;
			}
			std::cout << "[" << i << "] = " << dedicated_prime << std::endl;
			dedicated_prime += 2;
		}
		found_prime = _primes.back();
	} else if (nth > (current_size / 2)) {
		auto it = _primes.rbegin();
		auto pos = 1;
		while (pos < (_primes.size() - nth + 1)) {
			it++;
			pos++;
		}
		found_prime = *it;
	} else {
		auto it = _primes.begin();
		auto pos = 1;
		while (pos < nth) {
			it++;
			pos++;
		}
		found_prime = *it;
	}

	return found_prime;
}

bool PrimeNumber::add_if_prime(unsigned long long n) {
	unsigned long long square;

	for (auto const &i : _primes) {
		square = i * i;
		if (square <= n) {
			if (n % i == 0) {   // not prime
				break;
			}
		} else {
			break;
		}
	}

	if (square > n) {
		_primes.push_back(n);
		return true;
	} else {
		return false;
	}
}
