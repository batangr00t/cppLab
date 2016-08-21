#include <iostream>

using namespace std;

class CPoint {
private:

public:
	int x;
	int y;

	CPoint( int n ) : x(n), y(n) {
		cout << __PRETTY_FUNCTION__ << x << endl;
	};

	CPoint( const CPoint& p ) {
		x = p.x;
		y= p.y;
		cout << __PRETTY_FUNCTION__ << x << endl;
	};

	~CPoint() {
		cout << __PRETTY_FUNCTION__ << x << endl;
	}

	void show() {
		x = x +1;
		cout << x << "," << y << "," << endl;
	}

	void operator=( const CPoint& p ) {
		cout << __PRETTY_FUNCTION__ << endl;
	}

	void setX( int n ) {
		x = n;
	}

};

CPoint print( CPoint& p ) {
	//CPoint p2(200);

	return p;
}

int main(int argc, char * argv[]) {

	cout << "---------- start -----------------" << endl;

	 CPoint p1(100);

	cout << "---------- b print -----------------" << endl;
	p1 = print(p1);
	p1.show();
	cout << "---------- a print -----------------" << endl;

	cout << "----------  end  -----------------" << endl;
}
