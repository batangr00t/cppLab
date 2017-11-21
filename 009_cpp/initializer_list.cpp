#include <iostream>
#include <initializer_list>

using namespace std;

string sum( string start, initializer_list<string> strs ) {
	string sum(start);
	sum.reserve( 100 );
	for ( const auto& e : strs) {
		sum += e;
	}
	cout << "sum.capacity() = " << sum.capacity() << endl;
	return sum;
}

int sum( initializer_list<int> l ) {
	int sum = 0;
	for ( const auto& e : l) {
		sum += e;
	}
	return sum;
}

int main(int argc, char * argv[] ) {
	cout << "---------- start -----------------" << endl;

	initializer_list<int> list = { 1, 2, 3, 4, 5 };

	for ( const auto& e : list) {
		cout << e << endl;
	}

	cout << "sum = " << sum( list ) << endl;
	cout << "sum2 = " << sum( {1, 2, 3} ) << endl;

	cout << "sum3 = " << sum( "good", {"morning", "cho", "juik"} ) << endl;

	string name = "cho juik";
	cout << "sum3 = " << sum( "good", {"morning", name} ).capacity() << endl;

	cout << "----------  end  -----------------" << endl;
}
