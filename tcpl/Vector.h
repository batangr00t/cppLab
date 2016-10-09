/*
 * Vector.h
 *
 *  Created on: 2016. 10. 9.
 *      Author: cho
 */

#ifndef TCPL_VECTOR_H_
#define TCPL_VECTOR_H_

#include <initializer_list>
#include <ostream>

class Vector {
private:
	double * elem;
	int sz;

public:
	// constructor
	Vector();
	Vector(int s);
	Vector(std::initializer_list<double> lst);

	// destructor
	virtual ~Vector();

	// copy constructor
	Vector(const Vector& v);

	// copy assignment
	Vector& operator=(const Vector& v);

	double& operator[](int i);
	const double& operator[](int i) const;

	int size() const;

	// print contents of Vector
	friend std::ostream& operator<<( std::ostream& os, const Vector& v);
};

#endif /* TCPL_VECTOR_H_ */
