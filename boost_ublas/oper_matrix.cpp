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
//#include "io.hpp"

using namespace std;
namespace ublas = boost::numeric::ublas;

/// number of data
const unsigned int N = 5;

int main() {
	cout << "==== START " << endl;
	random_device rd;     // seed, rd()
	mt19937_64 gen(4);    // random number generator

	ublas::vector<double> t (N); // time vector, sec
	for (unsigned i = 0; i < t.size(); ++i) t(i) = i+1;
	cout << "t("<<N<<") = " << t << endl;

	uniform_int_distribution<int> dis_y( 0, 10 );
	ublas::vector<double> y (N); // measured value
	for (unsigned i = 0; i < y.size(); ++i) y(i) = dis_y(gen);
	cout << "y("<<N<<") = " << y << endl;

	//const double m_init[N][N] = { {1, 2}, {3, 4} };
	ublas::matrix<double> m( N, N );
	for (unsigned i = 0; i < m.size1 (); ++ i)
		for (unsigned j = 0; j < m.size2 (); ++ j)
			m (i, j) = i*2 + j + 1;
			//m(i,j) = m_init[i][j];
	m(N-1,N-1) = 3;
	cout << "matrix = " << m << endl;

	cout << "\n==== standard operation : +, -, *(scalar), /(scalar) " << endl;
	{
		cout << "t+y = " << t+y << endl;
		cout << "t-y = " << t-y << endl;
		cout << "2*t = " << 2*t << endl;
		cout << "t*3 = " << t*3 << endl;
		cout << "t/2 = " << t/3 << endl;
		cout << "-t  = " << -t << endl;
	}

	cout << "\n==== inner, outer and other products " << endl;
	{
		cout << "inner_prod(t, y) = " << inner_prod( t, y ) << endl;
		cout << "inner_prod(y, t) = " << inner_prod( y, t ) << endl;
		cout << "outer_prod(t, y) = " << outer_prod( t, y ) << endl;
		cout << "outer_prod(y, t) = " << outer_prod( y, t ) << endl;
		cout << "element_prod(t, y) = " << element_prod(t, y) << endl;
		cout << "element_prod(y, t) = " << element_prod(y, t) << endl;
		cout << "element_div(t, y)  = " << element_div(t, y) << endl;
		cout << "element_div(y, t)  = " << element_div(y, t) << endl;
		cout << "prod(m, t)  = " << prod(m, t) << endl;
		cout << "prod(t, m)  = " << prod(t, m) << endl;
		cout << "prec_prod(t, m)  = " << prec_prod(t, m) << endl;
		cout << "prec_prod(m, t)  = " << prec_prod(m, t) << endl;
	}

	cout << "\n==== transformations " << endl;
	{
		cout << "trans(m) = " << ublas::trans(m) << endl;
	}

	cout << "\n==== triangular matrix " << endl;
	{
		auto L  = ublas::triangular_adaptor<ublas::matrix<double>, ublas::lower> (m);
		auto SL = ublas::triangular_adaptor<ublas::matrix<double>, ublas::strict_lower> (m);
		auto UL = ublas::triangular_adaptor<ublas::matrix<double>, ublas::unit_lower> (m);
		cout << "lower        L  = " << L << endl;
		cout << "strict lower SL = " << SL << endl;
		cout << "unit lower   UL = " << UL << endl;

		auto U =  ublas::triangular_adaptor<ublas::matrix<double>, ublas::upper> (m);
		auto SU = ublas::triangular_adaptor<ublas::matrix<double>, ublas::strict_upper> (m);
		auto UU = ublas::triangular_adaptor<ublas::matrix<double>, ublas::unit_upper> (m);
		cout << "upper        U  = " << U << endl;
		cout << "strict upper SU = " << SU << endl;
		cout << "unit upper   UU = " << UU << endl;

		cout << "prod( U, m ) = " << prod(U, m) << endl;

		ublas::vector<double> x(m.size1());
		ublas::vector<double> b(m.size1(), 1);
		cout << "inplace_solve(UL, b, ) : b = " << b << endl;
		inplace_solve( UL, b, ublas::unit_lower_tag() );
		cout << "inplace_solve(UL, b, ) : b = " << b << endl;
		cout << "prod( UL, b ) = " << prod( UL, b ) << endl;
	}

	cout << "\n==== pumutation matrix " << endl;
	{
		ublas::permutation_matrix<size_t> pm(N);
		pm(0) = 1;
		cout << "-- pm = " << pm << endl;
		ublas::swap_rows( pm, m);
		cout << "-- swap_rows( pm, m) = " << m << endl;
		pm(0) = 0; pm(1) = 0;
		cout << "-- pm = " << pm << endl;
		ublas::swap_rows( pm, m);
		cout << "-- swap_rows( pm, m) = " << m << endl;
		pm(0) = 0; pm(1) = 1; pm(2) = 0;
		cout << "-- pm = " << pm << endl;
		ublas::swap_rows( pm, m);
		cout << "-- swap_rows( pm, m) = " << m << endl;
	}

	cout << "\n==== LU factorization" << endl;
	{
		ublas::matrix<double> A(m);
		ublas::permutation_matrix<double> pm(N);
		cout << "-- pm = " << pm << endl;
		bool singular = ublas::lu_factorize( A, pm);
		cout << "-- return = " << singular << endl;
		cout << "-- A  = " << A << endl;
		cout << "-- pm = " << pm << endl;

		auto L = ublas::triangular_adaptor<ublas::matrix<double>, ublas::unit_lower>(A);
		cout << "-- L = " << L << endl;
		auto U = ublas::triangular_adaptor<ublas::matrix<double>, ublas::upper>(A);
		cout << "-- U = " << U << endl;
		cout << "-- LU = " << prod(L,U) << endl;
		ublas::matrix<double> pmA( m ); // pmA means pm*A, at first init as m
		swap_rows(pm, pmA);
		cout << "-- swap_rows(pm,A) = " << pmA << endl;

		cout << "-- solve Lz = b -------------" << endl;
		ublas::vector<double> b( N ); b(0) = 1; b(1) = 2; b(2) = 3;
		ublas::vector<double> z( b );
		cout << "-- L " << L << endl;
		cout << "-- b " << b << endl;
		ublas::inplace_solve( A, z, ublas::unit_lower_tag() );
		cout << "-- z = " << z << endl;
		cout << "-- confirm Lz = " << prod( L, z ) << endl;

		cout << "-- solve Ux = z -------------" << endl;
		ublas::vector<double> x( z );
		cout << "-- U " << U << endl;
		cout << "-- z " << z << endl;
		inplace_solve( A, x, ublas::upper_tag() );
		cout << "-- x = " << x << endl;
		cout << "-- confirm Ux = " << prod( U, x ) << endl;
	}

	cout << "==== END " << endl;
}
