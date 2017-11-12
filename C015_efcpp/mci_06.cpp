/*
 * mci_06.cpp
 *
 *  Created on: 2017. 11. 11.
 *      Author: cho
 */
#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

using namespace std;
using namespace boost::typeindex;

vector<bool> features() {
	return vector<bool>{ true, false, false, true, true };
}

void process( bool param ) {
	cout << "param is " << param << endl;
}

int main() {
	cout << "---- start ----" << endl;

	bool priority    = features()[0];
	auto isLargeSize = features()[1];

	cout << type_id_with_cvr<decltype(priority)>().pretty_name() << endl;
	cout << type_id_with_cvr<decltype(isLargeSize)>().pretty_name() << endl;

	process( priority );
	process( isLargeSize );

	cout << "----  end  ----" << endl;
}


