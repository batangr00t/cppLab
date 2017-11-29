
#include <iostream>
#include <functional>

using namespace std;

class A {
public:
	A():n(1) {
		cout << this << " : " << __PRETTY_FUNCTION__ << ", " << n << endl;
	}
	A(int a):n(a) {
		cout << this << " : " << __PRETTY_FUNCTION__ << ", " << n << endl;
	}
	A(const A& a) {
		this->n = a.n;
		cout << this << " : " << __PRETTY_FUNCTION__ << ", " << n << endl;
	}
	A(const A&& a) {
		this->n = a.n;
		cout << this << " : " << __PRETTY_FUNCTION__ << ", " << n << endl;
	}
	~A() {
		cout << this << " : " << __PRETTY_FUNCTION__ << ", " << n << endl;
	}

	friend ostream& operator<<( ostream& os, const A& a);
private:
	int n;
};

ostream& operator<<( ostream& os, const A& a) {
	os << &a << " : " << a.n;
	return os;
}

//void func( A a ) {
//	cout << "copy " << a << endl;
//}

void func( A& a ) {
	cout << "lvalue ref " << a << endl;
}

void func( A&& a ) {
	cout << "rvalue ref " << a << endl;
}

int main() {
	cout << "------- start --- " << endl;

	A a = A(5);
	A &ra = a;
	A c;

	cout << "------- func 1--- " << endl;
	func( a );
	cout << "------- func 2--- " << endl;
	func( ra );
	cout << "------- func 3--- " << endl;
	func( A() );
	cout << "------- func 4--- " << endl;
	func( move(a) );
	cout << "------- func 5--- " << endl;
	A b( A() );
	cout << a << endl;
	//cout << b << endl;

	cout << "------- end --- " << endl;
}

