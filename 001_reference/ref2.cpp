/*
 * ref.cpp
 *
 *  Created on: 2016. 4. 13.
 *      Author: juik
 */

// for more infomation
// see http://en.cppreference.com/w/cpp/language/value_category

#include <iostream>
#include <functional>
#include <list>
#include "../001_reference/Box.h"

using namespace std;

Box a = Box("global_box");

void para_value( Box b ) {
	cout << "--------start para_value() " << endl;
	cout << b << endl;
	b.setName("para_value");
	cout << "--------end para_value() " << endl;
}

void para_ref( Box& b ) {
	cout << "--------start para_ref() " << endl;
	cout << b << endl;
	b.setName("para_ref");
	cout << "--------end para_ref() " << endl;
}

void para_rvalue( Box&& b ) {
	cout << "--------start para_rvalue() " << endl;
	cout << b << endl;
	b.setName("para_rvalue");
	cout << "--------end para_rvalue() " << endl;
}

void para_pointer( Box* b ) {
	cout << "--------start para_pointer() " << endl;
	cout << *b << endl;
	b->setName("para_pointer");
	cout << "--------end para_pointer() " << endl;

}

Box ret_value() {
	a.setName("ret_value");
	return a;
}

Box& ret_ref() {
	return a;
}

Box&& ret_rvalue() {
	a.setName("ret_rvalue");
	return move(a);
	//return a;     //  error: cannot bind 'Box' lvalue to 'Box&&'
}

Box* ret_pointer() {
	Box *p = &a;
	return p;
}

int main() {
	cout << "\n====== start ==============================" << endl;

	cout << "\n----para_value() " << endl;
	para_value( a );		// a temporary object, cons/dest
	cout << a << endl;

	cout << "\n----para_ref() " << endl;
	para_ref( a );			// good! does not create a temporary object.
	cout << a << endl;

	cout << "\n----para_rvalue(move(a)) " << endl;
	//para_rvalue( a ); 	// error: cannot bind 'Box' lvalue to 'Box&&'
	para_rvalue( move(a) ); // good! does not create a temporary object.
	cout << a << endl; 		// 'a' is still a valid object.

	cout << "\n----para_pointer() " << endl;
	para_pointer( &a );			// does not create an object

	cout << "\n----ret_value() " << endl;
	Box rvBox = ret_value();		// copy constructor

	cout << "\n----ret_ref() " << endl;
	Box &rrBox = ret_ref();			// does not create an object

	cout << "\n----Box &&b = ret_rvalue() " << endl;
	Box &&rrvBox = ret_rvalue();	// does not create an object

	cout << "----ret_rvalue() " << endl;
	ret_rvalue();					// does not create an object

	cout << "----Box b = ret_rvalue() " << endl;
	Box cBox = ret_rvalue();		// copy constructor

	cout << "\n----ret_pointer() " << endl;
	Box *rpBox = ret_pointer();		// does not create an object

	cout << "\n====== end ==============================" << endl;
	return 0;
} 	// destructor

/* result
Box::Box(const string&) = 0x100408000:Box("global_box")

====== start ==============================

----para_value()
Box::Box(const Box&) = 0xffffcbb0:Box("global_box")
--------start para_value()
0xffffcbb0:Box("global_box")
--------end para_value()
virtual Box::~Box() = 0xffffcbb0:Box("para_value")
0x100408000:Box("global_box")

----para_ref()
--------start para_ref()
0x100408000:Box("global_box")
--------end para_ref()
0x100408000:Box("para_ref")

----para_rvalue(move(a))
--------start para_rvalue()
0x100408000:Box("para_ref")
--------end para_rvalue()
0x100408000:Box("para_rvalue")

----para_pointer()
--------start para_pointer()
0x100408000:Box("para_rvalue")
--------end para_pointer()

----ret_value()
Box::Box(const Box&) = 0xffffcba0:Box("ret_value")

----ret_ref()

----Box &&b = ret_rvalue()
----ret_rvalue()
----Box b = ret_rvalue()
Box::Box(const Box&) = 0xffffcb90:Box("ret_rvalue")

----ret_pointer()

====== end ==============================
virtual Box::~Box() = 0xffffcb90:Box("ret_rvalue")
virtual Box::~Box() = 0xffffcba0:Box("ret_value")
virtual Box::~Box() = 0x100408000:Box("ret_rvalue")

 */
