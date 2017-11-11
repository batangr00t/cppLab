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
const unsigned int N = 15;
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
	cout << "==== START " << endl;
	random_device rd;     // seed, rd()
	mt19937_64 gen(rd());    // random number generator

	ublas::vector<double> t (N); // time vector, sec
	for (unsigned i = 0; i < t.size(); ++i) t(i) = (i+1);
	cout << "t("<<N<<") = " << t << endl;

	uniform_int_distribution<int> dis_y( -10, 10 );
	ublas::vector<double> y (N); // measured value
	for (unsigned i = 0; i < y.size(); ++i) y(i) = dis_y(gen);
	cout << "y("<<N<<") = " << y << endl;

	cout << "==== compute polynomial fitting from data t(time) and y(value)" << endl;
	cout << "==== find coefficients of 2nd oder polynomial, y = a0 + a1*x + a2*x^2" << endl;

	cout << "-- make Vandermonde matrix X " << endl;
	ublas::matrix<double> X(N, order);                 // X = Vandermonde matrix
	ublas::column(X, 0) = ublas::vector<double>(N, 1); // 0 column = t^0, all one
	ublas::column(X, 1) = t;                           // 1 column = t^1, t itself
//	ublas::column(X, 2) = ublas::element_prod(t, t);   // 2 column = t^2
	for ( unsigned j = 2; j<order; ++ j ) {
		ublas::column(X, j) = element_prod(t, ublas::column(X, j-1));
	}
	cout << "X         = " << X << endl;
	cout << "trans(X)  = " << trans(X) << endl;

	ublas::matrix<double> M = prod( trans(X), X );
	cout << "M = trans(X) x X = " << M << endl;

	ublas::vector<double> Y = prod( trans(X), y );
	cout << "Y = trans(X) x y = " << Y << endl;

	cout << endl;
	cout << "==== solve the equation : M x a = Y by LU factorization" << endl;
	cout << "====      LU=PM and PM x a = PY" << endl;
	cout << "====      so,       LU x a = PY" << endl;
	ublas::permutation_matrix<double> pm(M.size1());
	ublas::vector<double> a( Y );                           //  a <- Y
	ublas::matrix<double> LU( M );                          // LU <- M
	bool singular = ublas::lu_factorize( LU, pm);           // LU <- LU
	if ( singular ) {
		cout << "ERROR!!! " << endl;
	} else {
		cout << "LU = " << LU << endl;
		cout << "Y  = " << Y << endl;
		cout << "pm = " << pm << endl;
		ublas::swap_rows( pm, a);                              // a <- PY
		ublas::inplace_solve( LU, a, ublas::unit_lower_tag()); // a <- z : Lz = PY
		ublas::inplace_solve( LU, a, ublas::upper_tag());      // a <- x : Ux = z
		cout << "polynomial coefficient = " << a << endl;
		cout << "prod( M, a ) = " << prod( M, a ) << endl;
	}

	cout << endl;
	cout << "==== y = "<< a(0) << " + (" << a(1) << ")*x + ("<< a(2) << ")*x^2" << endl;
	cout << "==== y(1) = " << a(0) + a(1) + a(2);
	cout << ",    y(2) = " << a(0) + a(1)*2 + a(2)*2*2;
	cout << ",    y(3) = " << a(0) + a(1)*3 + a(2)*3*3 << endl;

	cout << "==== run 10 times" << endl;
	for ( int cnt = 0; cnt < 10; ++ cnt  ) {
		cout << endl;
		cout << "[" << cnt << "] t = " << t << endl;

		for (unsigned i = 0; i < y.size(); ++i) y(i) = dis_y(gen);
		cout << "[" << cnt << "] y = " << y << endl;

		ublas::vector<double> a( prod( trans(X), y ) );  // a <- trans(X) x y
		ublas::swap_rows( pm, a); // a <- PY
		ublas::inplace_solve( LU, a, ublas::unit_lower_tag()); // a <- z : Lz = PY
		ublas::inplace_solve( LU, a, ublas::upper_tag());      // a <- x : Ux = z
		cout << "polynomial coefficient = " << a << endl;
		cout << "[" << cnt << "] ";
		for ( double x : t ) {
			cout << "y(" << x << ") = " << polyval(a, x) << ", ";
		}
		cout << endl;
	}

	// generate data for plot
	cout << "============== plot data ===========" << endl;
	cout << "t, y, polyval_y" << endl;
	for ( unsigned i = 0; i < 20; ++i ) {
		y(0) = dis_y(gen);
		for (unsigned i = 1; i < y.size(); ++i) y(i) = y(i-1) + dis_y(gen);
		ublas::vector<double> a( prod( trans(X), y ) );
		ublas::lu_substitute( LU, pm, a );
		for ( unsigned j = 0; j < N; ++ j ) {
			cout << t(j) << "," << y(j) << "," << polyval(a, t(j)) << endl;
		}
	}

	cout << "==== END " << endl;
}
