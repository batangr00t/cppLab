/*
 * ex_main.cpp
 *
 *  Created on: 2017. 6. 6.
 *      Author: cho
 */

#include <random>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>
//#include "io.hpp"

using namespace std;
namespace ublas = boost::numeric::ublas;

/// number of data
const unsigned int N = 3;

int main () {
	// random number generator
	random_device rd;      // obtain seed
	mt19937_64 gen(rd());  // mersenne twister engine

	// vector
	cout << "============== vector" << endl;
	{
		ublas::vector<double> t (N); // time vector, sec
		for (unsigned i = 0; i < t.size(); ++i) t(i) = i;
		cout << "t("<<N<<") = " << t << endl;

		uniform_int_distribution<int> dis_y( 0, 10 );
		ublas::vector<double> y (N); // measured value
		for (unsigned i = 0; i < y.size(); ++i) y(i) = dis_y(gen);
		cout << "y("<<N<<") = " << y << endl;

		for (unsigned i = 0; i < N; ++i) {
			ublas::unit_vector<double> u(N, i);
			cout << "unit_vector("<<N<<","<<i<<") = " << u << endl;
		}

		ublas::zero_vector<double> z(N);
		cout << "zero_vector("<<N<<") = " << z << endl;

		ublas::scalar_vector<double> s(N, 3);
		cout << "scalar_vector("<<N<<",3) = " << s << endl;

		ublas::scalar_vector<double> one(N, 1);
		cout << "one("<<N<<",1) = " << one << endl;
	}

	// range
	cout << "============== range, slice" << endl;
	{
		ublas::range r1(0, N);
		for (unsigned i = 0; i < r1.size(); ++ i) {
			cout << "range(0,N) r("<<i<<") = " << r1(i) << endl;
		}

		ublas::range r2(3, N);
		for (unsigned i = 0; i < r2.size(); ++ i) {
			cout << "range(3,N) r("<<i<<") = " << r2(i) << endl;
		}

		ublas::slice s2(0, 2, N);
		for (unsigned i = 0; i < s2.size(); ++ i) {
			cout << "slice(0,2,N) s2("<<i<<") = " << s2(i) << endl;
		}

		ublas::slice s3(1, 3, N);
		for (unsigned i = 0; i < s3.size(); ++ i) {
			cout << "slice(1,3,N) s("<<i<<") = " << s3(i) << endl;
		}
	}

	// matrix
	cout << "============== matrix" << endl;
	{
		ublas::matrix<double> m;
		cout << "m()          = " << m << endl;

		m.resize( N, N );
		cout << "m.resize(N,N)= " << m << endl;

		m.clear();
		cout << "m.clear()    = " << m << endl;

		for (unsigned i = 0; i < m.size1 (); ++ i)
			for (unsigned j = 0; j < m.size2 (); ++ j)
				m (i, j) = i*10 + j;
		cout << "matrix       = " << m << endl;

		cout << "transpose    = " << ublas::trans(m) << endl;
		cout << "column(m, 1) = " << ublas::column (m, 1) << endl;
		cout << "column(m, 2) = " << ublas::column (m, 2) << endl;
		cout << "row(m, 1)    = " << ublas::row (m, 1) << endl;
		cout << "row(m, 2)    = " << ublas::row (m, 2) << endl;
		cout << "project(m, range(0,1), range(0,N))     = "
				<< ublas::project(m, ublas::range(0,1), ublas::range(0,N)) << endl;
		cout << "project(m, range(N-1,N), range(N-1,N)) = "
				<< ublas::project(m, ublas::range(N-1,N), ublas::range(N-1,N)) << endl;
		cout << "project(m, slice(1,2,2), slice(1,2,2)) = "
				<< ublas::project(m, ublas::slice(0,2,2), ublas::slice(0,2,2)) << endl;

		auto m_temp = m;
		for ( unsigned i = 0; i < m_temp.size2(); ++i ) {
			ublas::column( m_temp, i) = ublas::scalar_vector<double>(m_temp.size1(),1);
			cout << "m_temp       = " << m_temp << endl;
		}

		m_temp = m;
		for ( unsigned i = 0; i < m_temp.size1(); ++i ) {
			ublas::row( m_temp, i ) = ublas::scalar_vector<double>(m_temp.size2(),1);
			cout << "m_temp       = " << m_temp << endl;
		}

		ublas::identity_matrix<double> mi(N);
		cout << "identity(N)      = " << mi << endl;

		ublas::zero_matrix<double> zero(N);
		cout << "zero(N)          = " << zero << endl;

		ublas::scalar_matrix<double> ones(1, 1, 1);
		cout << "sizeof( scalar_matrix(1, 1, 1) ) = " << sizeof(ones) << endl;
		ublas::scalar_matrix<double> twos(1000, 2000000, 2);
		cout << "sizeof( scalar_matrix(1000, 2000000, 2) ) = " << sizeof(twos) << endl;

		ublas::matrix<double> ones1(1, 1, 1);
		cout << "sizeof( matrix(1, 1, 1) ) = " << sizeof(ones1) << endl;
		ublas::matrix<double> twos1(10000, 20000, 2);
		cout << "sizeof( matrix(10000, 20000, 2) ) = " << sizeof(twos1) << endl;
	}

	// matrix
	cout << "============== triangular_matrix" << endl;
	{
		ublas::triangular_matrix<double, ublas::lower> l(N,N);
		for ( unsigned i = 0; i < l.size1(); ++i )
			for ( unsigned j = 0; j <= i; ++j )
				l(i,j) = 10*i + j;
		cout << "l(N, N)           = " << l << endl;

		ublas::triangular_matrix<double, ublas::unit_lower> ul(N,N);
		for ( unsigned i = 0; i < ul.size1(); ++i )
			for ( unsigned j = 0; j < i; ++j )
				ul(i,j) = 10*i + j;
		cout << "ul(N, N)          = " << ul << endl;

		ublas::triangular_matrix<double, ublas::upper> u(N,N);
		for ( unsigned i = 0; i < u.size1(); ++i )
			for ( unsigned j = i; j < u.size2(); ++j )
				u(i,j) = 10*i + j+1;
		cout << "u(N, N)           = " << u << endl;

		ublas::triangular_matrix<double, ublas::unit_upper> uu(N,N);
		for ( unsigned i = 0; i < uu.size1(); ++i )
			for ( unsigned j = i+1; j < uu.size2(); ++j )
				uu(i,j) = 10*i + j+1;
		cout << "uu(N, N)          = " << uu << endl;
	}
}


