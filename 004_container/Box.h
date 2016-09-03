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
	Box(const Box&);
	Box(const Box&&);
	Box(const string&);
	Box(int);
	virtual ~Box();
	const string& getName() const;
	int getId() const;
	void setName(const string&);
	void operator=(const Box&);
	friend ostream& operator<< ( ostream& os, const Box &b );
private:
	static int seq;
	string _name;
	int _id;
};

#endif /* BOX_H_ */
