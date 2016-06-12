#include <vector>
#include <iostream>
#include <stdlib.h>
#include "PrimeNumber.h"

using namespace std;

int main(int argc, char * argv[] ) {
	cout << "---------- start -----------------" << endl;

	unsigned int n = 10;
	PrimeNumber primes;

	if ( argc > 1 ) n = atoi( argv[1]);

	cout << primes.at(n) << endl;

	//cout << primes.at(100000) << endl;

//	for ( int i=1; i<=n; i++ ) {
//		cout << i << " : " << primes.at(i) << endl;
//	}

	cout << "----------  end  -----------------" << endl;
}
