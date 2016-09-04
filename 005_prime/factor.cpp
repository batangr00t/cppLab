#include <vector>
#include <iostream>
#include <stdlib.h>
#include "PrimeNumber.h"

using namespace std;

vector<unsigned long long> primes;
vector<unsigned long long> factors;

bool isPrime( unsigned long long n ) {
	bool isPrime = true;

	for ( unsigned long long p : primes ) {
		if ( p*p  > n ) break;

		if ( n%p == 0 ) {
			isPrime = false;
			break;
		}
	}

	if ( isPrime ) primes.push_back(n);

	return isPrime;
}

int main(int argc, char * argv[] ) {
	cout << "---------- start -----------------" << endl;

	unsigned long long n = 10;


	if ( argc > 1 ) n = atoi( argv[1]);
	cout << n << " = ";

	primes.push_back(2);
	while ( n%2 == 0 ) {
		factors.push_back(2);
		n = n/2;
	}

	for ( int i=3; i <= n; i += 2 ) {
		// if i prime add primes.
		if ( isPrime(i) ) {
			if ( n%i == 0 ) {
				factors.push_back(i);
				n = n/i;
			}
		}
	}


	for ( auto it = factors.begin(); it != factors.end(); ) {
		cout << *it;
		if ( (++it) != factors.end() ) cout << " x ";
	}

	cout << endl;

	cout << "----------  end  -----------------" << endl;
}
