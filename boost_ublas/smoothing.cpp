/*
 * oper_matrix.cpp
 *
 *  Created on: 2017. 6. 6.
 *      Author: cho
 */

#include <random>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace std;
namespace ublas = boost::numeric::ublas;

/// number of data
const unsigned int N = 30;
const int order = 3; // 3 means second order polynomial

// return polynomial value
// ex, return y = a0 + a1*x + a2*x^2
double polyval( const ublas::vector<double>& a, const double x ) {
	ublas::vector<double> tmp(a);

	for ( unsigned i = 1; i < a.size(); ++i ) {
		for ( unsigned j = i; j < a.size(); ++j )
			tmp(j) *= x;
	}

	return ublas::sum( tmp );
}

int main() {
	random_device rd;     // seed, rd()
	mt19937_64 gen(rd());    // random number generator

	ublas::vector<double> t (N); // time vector, sec
	for (unsigned i = 0; i < t.size(); ++i) t(i) = (i+1);
	//cout << "t("<<N<<") = " << t << endl;

	//uniform_int_distribution<int> dis_y( -10, 10 );
	normal_distribution<float> dis_y( 0, 10 );
	ublas::vector<double> y (N); // measured value
	for (unsigned i = 0; i < y.size(); ++i) y(i) = dis_y(gen);
	//cout << "y("<<N<<") = " << y << endl;

	ublas::matrix<double> X(N, order);                 // X = Vandermonde matrix
	ublas::column(X, 0) = ublas::vector<double>(N, 1); // 0 column = t^0, all one
	ublas::column(X, 1) = t;                           // 1 column = t^1, t itself
	for ( unsigned j = 2; j<order; ++ j ) {
		ublas::column(X, j) = element_prod(t, ublas::column(X, j-1));
	}

	ublas::matrix<double> M = prod( trans(X), X );

	cout << endl;
	ublas::permutation_matrix<double> pm(M.size1());
	ublas::matrix<double> LU( M );                          // LU <- M
	bool singular = ublas::lu_factorize( LU, pm);           // LU <- LU
	if ( singular ) {
		cout << "ERROR!!! " << endl;
		return EXIT_FAILURE;
	}

	// continuous value y
	cout << "y, lowpass, polyval t" << endl;
	for ( unsigned i = 0; i < 200; ++i ) {
		// generate y
		for (unsigned i = 1; i < y.size(); ++i) y(i-1) = y(i); // left shift
		y(y.size()-1) += dis_y(gen);                           // append 1 element

		// backup y
		double bakup_y = y(y.size()-1);
		if ( i == 100 ) y(y.size()-1) = 0;

		// y
		cout << y(N-1);
		static double lpv = y(N-1);

		// low-pass filter, alpha = 0.5
		lpv = lpv/2 + y(N-1)/2;
		cout << "," << lpv;

		// polyval t
		ublas::vector<double> tmp_y( y );
		ublas::vector<double> a( prod( trans(X), tmp_y ) );
		ublas::lu_substitute( LU, pm, a );
		cout << "," << polyval(a, t(N-1));

		// restore
		y(y.size()-1) = bakup_y;

		cout << endl;
	}
}
