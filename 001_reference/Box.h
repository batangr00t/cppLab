/*
 * Box.h
 *
 *  Created on: 2016. 4. 13.
 *      Author: juik
 */

#ifndef BOX_H_
#define BOX_H_
#include <iostream>

using namespace std;

class Box {
public:
	Box();
	Box(const string&);
	Box(const Box&);
	virtual ~Box();
	const string& getName();
	void setName(const string&);
	friend ostream& operator<< ( ostream& os, const Box &b );
private:
	string _name;
};

#endif /* BOX_H_ */
