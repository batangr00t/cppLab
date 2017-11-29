#include <iostream>
#include <map>
#include "Box.h"

using namespace std;

map<string, Box> getBox() {
	map<string, Box> boxes;

	boxes.emplace("default", Box());

	return boxes;
}

int main() {
	cout << "---- start --- " << endl;

	auto bs = getBox();

	cout << "---- for --- " << endl;
	for ( const auto& e : bs ) {
		string desc;
		Box b;
		tie( desc, b) = e;
		cout << desc << " => " << b << endl;
	}

	cout << "---- end --- " << endl;
}


