#include <iostream>
#include <vector>
using namespace std;


class Ca {
public:
	int x;

	Ca( int n ) {
		cout << __PRETTY_FUNCTION__ << n << endl;
		x = n;
	}

	Ca( const Ca& c ) {
		cout << __PRETTY_FUNCTION__ << c.x << endl;
		x = c.x;
	}

	~Ca() {
		cout << __PRETTY_FUNCTION__ << x << endl;
	}
};

void print( Ca& c ) {
	c.x = c.x + 1;
	cout << c.x << endl;
}

Ca& inc( Ca& c) {
	c.x = c.x + 1;
	Ca error(900);
	return error;
}

int main() {
	vector<Ca> list;

	cout << " push_back ----------- " << endl;
	list.reserve(3);
	list.emplace_back( 100 );
	list.emplace_back( 200 );
	list.emplace_back( 300 );

	cout << " for ----------- " << endl;
	for( Ca& c : list ) {
		//cout << " 11111 " << endl;
		print( c );
		//cout << " 22222 " << endl;
	}

	cout << " for ----------- " << endl;
	Ca c1(1);
	inc( c1 );
	cout << " end ----------- " << endl;
}
