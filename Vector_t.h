#ifndef _VECTOR_T_H_
#define _VECTOR_T_H_

#include <cmath>
#include <iostream>
#include "Point_t.h"

using namespace std;

class Vector_t
{
public:
	double x, y, z;

	Vector_t(double xx, double yy, double zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}

	Vector_t(Vector_t& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	Vector_t& operator=(const Vector_t& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	Vector_t& operator-() const
	{
		return Vector_t(-x, -y, -z);
	}

	double length()
	{
		return (double) sqrt(x*x + y*y + z*z);
	}

	void makeUnitVector()
	{
		double scale = 1.0/this.length();
		x *= scale;
		y *= scale;
		z *= scale;
	}
};

#endif
