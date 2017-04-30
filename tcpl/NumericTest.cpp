#include <boost/timer/timer.hpp>
#include <iostream>
#include <random>
#include <cmath>

using namespace std;

int main() {

	boost::timer::cpu_timer timer;
	int count = 1000*1000;
	random_device rd;
	minstd_rand minstd_rng(rd());
	mt19937 mt_rng(rd());
	normal_distribution<double> ndist(0,100);
	uniform_real_distribution<double> udist(-1, 1);

	// min max
	cout << "--- modf" << endl;
	cout << "------ modf() " << count << endl;
	{
		double f;
		double integral_part;
		double fractional_part;

		timer.start();
		for ( int i = 0; i< count; ++i ) {
			f = udist(minstd_rng);
			fractional_part = modf( f, &integral_part );
		}
		timer.stop();

		cout << "f               = " << f << " ( " << std::hexfloat << f << " )" << std::defaultfloat << endl;
		cout << "integral_part   = " << integral_part << " ( " << std::hexfloat << integral_part << " )" << std::defaultfloat <<endl;
		cout << "fractional_part = " << fractional_part << " ( " << std::hexfloat << fractional_part << " )" << std::defaultfloat <<endl;

		cout << "modf() " << timer.format() << endl;
	}

	return 0;
}


