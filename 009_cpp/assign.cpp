/*
 * oper.cpp
 *
 *  Created on: 2016. 6. 25.
 *      Author: juik
 */
#include <iostream>
#include <cstring>

using namespace std;

class CString {
private:
	int len;
	char *str;
public:
	CString(const char *s = "Unknown") {
		cout << __PRETTY_FUNCTION__ << s << endl;
		len = strlen(s);
		str = new char[len+1];
		strncpy( str, s, len);
	}

	~CString() {
		delete [] str;
	}

	CString& operator=( const CString& string ) {
		cout << __PRETTY_FUNCTION__ << *this << " = " << string << endl;
		len = string.len;

		delete [] str;
		str = new char[len+1];

		strncpy( str, string.str, len);

		return *this;
	}

	friend ostream& operator<<( ostream & os, const CString& str);
};

ostream& operator<<( ostream & os, const CString& str) {
	os << str.len << "*" << str.str << "*";
	return os;
}

int main() {
	CString str1 = "C++ Programming";
	CString str2 = "Hello C++";
	CString str3 = "Operator overloading";

	str1 = str2 = str3;

	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;
}
