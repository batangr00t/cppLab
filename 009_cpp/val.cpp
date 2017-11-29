#include <iostream>

using namespace std;

int& add( int& a, int b ) {
	a += b;
	return a;
}

// dangerous code
char* fun() { return "Hello"; }

int main() {
	cout << "------- start --- " << endl;
	int a = 0;
	int n = 3;
	*(&(n)) = 1 ;
	(++n) = 4;
	cout << n << endl;
	cout << (n++) << endl;
	cout << (n++) << endl;

	cout << "----- " << endl;

	add(a, 2) = 100;
	cout << a << endl;
	cout << "------- end --- " << endl;

	char* q = fun();
	cout << q << endl;
	q[0]='h';    // 예외발생, fun() 이 임시 메모리를 리턴하는데 거기 접근하려 한다.
}

