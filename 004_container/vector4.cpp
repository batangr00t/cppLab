#include <iostream>
#include <vector>
#include "Box.h"

using namespace std;

vector<Box> getBox() {
	vector<Box> boxes;

	{
		cout << "---- before emplace_back 1st--- " << endl;
		boxes.emplace_back( Box());
	}

	{
		cout << "---- before push_back --- " << endl;
		boxes.push_back( Box());
	}

	{
		cout << "---- before emplace_back 2nd --- " << endl;
		boxes.emplace_back( Box());
	}

	cout << "---- before return --- " << endl;
	return boxes;
}

int main() {
	cout << "---- start --- " << endl;

	auto bs = getBox();

	cout << "---- for --- " << endl;
	for ( const auto& e : bs ) {
		cout << e << endl;
	}

	cout << "---- end --- " << endl;
}
