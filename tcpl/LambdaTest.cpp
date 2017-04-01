#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// print all elements
void print_all( const vector<int>& v ) {
	cout << "{";
	for_each(v.begin(), v.end(), [](int e){ cout << e << ",";});
	cout << "}" << endl;
}
// This lambda requires no access to local variable
void algo( vector<int>& v) {
	sort(v.begin(), v.end(), [](int x, int y) { return abs(x) < abs(y); });
}

int main() {
	// create vector
	vector<int> emptyList;
	print_all(emptyList);
	algo(emptyList);
	print_all(emptyList);

	// create vector
	vector<int> intList { 1, 2, 3, -1, -5, 100, 23 };
	print_all(intList);

	// sort elements by abs value
	algo(intList);
	print_all(intList);

}
