#include <deque>
#include <iostream>

using namespace std;

int main() {
	cout << "---------- start -----------------" << endl;

	deque<char> stack;

	for ( int i=0; i<10; ++i ) stack.pop_back();

	cout << "----------  end  -----------------" << endl;
}
