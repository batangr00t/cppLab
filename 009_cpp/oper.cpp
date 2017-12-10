#include <iostream>

using namespace std;

class Point {
private:
	int _x;
	int _y;
public:
	Point( int a, int b ): _x(a), _y(b) {
		cout << this << __PRETTY_FUNCTION__<< *this << endl;
	}

	~Point() {
		cout << this << __PRETTY_FUNCTION__<< *this << endl;
	}

	Point operator+( const Point& p ) {
		cout << *this << " + " << p << endl;
		return Point( _x + p._x, _y + p._y );
	}

	Point& operator+=( const Point& p ) {
		cout << *this << " += " << p << endl;
		this->_x += p._x;
		this->_y += p._y;
		return *this;
	}

	Point& sum( const Point& p ) {
		cout << *this << " += " << p << endl;
		_x += p._x;
		_y += p._y;
		return *this;
	}

	Point& operator()( int n ) {
		_x += n;
		_y += n;
		return *this;
	}

	friend ostream& operator<<( ostream& os, const Point& p );
};

ostream& operator<<( ostream& os, const Point& p ) {
	os << "(" << p._x << "," << p._y << ")";
	return os;
}

int main() {
	cout << "------- start ---" << endl;

	Point p1 ( 1, 1 );
	Point p2 ( 2, 2 );
	Point p3 ( 3, 3 );

	cout << ( p1 + p2 + p3 ) << endl;

	Point p4(1,1);

	p4 += p1 += p2 += p3;

	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;
	cout << "p3 = " << p3 << endl;
	cout << "p4 = " << p4 << endl;

	Point p5(0,0);
	p5.sum(Point(1,1)).sum(Point(10,10)).sum(Point(20,100));
	cout << "p5 = " << p5 << endl;

	cout << "x = " << p5(0) << endl;
	cout << "y = " << p5(1) << endl;

	Point p6(0,0);
	p6(1)(200)(1000);
	cout << p6 << endl;

	cout << "before " << p2 << endl;
	p2.operator+=(p3);
	cout << "after  " << p2 << endl;


	cout << "------- end ---" << endl;
}

