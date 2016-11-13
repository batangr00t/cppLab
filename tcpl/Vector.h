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

	// copy
	Vector(const Vector& v);               // copy constructor
	Vector& operator=(const Vector& v);    // copy assignment

	// move
	Vector(Vector&& v);              // move constructor
	Vector& operator=(Vector&& v);   // move assignment

	// index operator, const and non-const
	double& operator[](int i);             // Vector v; v[0]
	const double& operator[](int i) const; // const Vector& v; v[0]

	int size() const;

	// operator+
	friend Vector operator+( const Vector& a, const Vector& b );

	// print contents of Vector
	friend std::ostream& operator<<( std::ostream& os, const Vector& v);
};

#endif /* TCPL_VECTOR_H_ */
