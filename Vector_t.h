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

	Vector_t()
	{
		
	}

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

	Vector_t operator-() const
	{
		 Vector_t v(-x, -y, -z);
		 return v;
	}

	Vector_t& operator+=(const Vector_t& v)
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;
		return *this;
	}

	Vector_t& operator*=(double s)
	{
		x*=s;
		y*=s;
		z*=s;
		return *this;
	}

	double length()
	{
		return (double) sqrt(x*x + y*y + z*z);
	}

	void normalizeVector()
	{
		double scale = 1.0/(this->length());
		x *= scale;
		y *= scale;
		z *= scale;
	}
};

Vector_t operator+(const Vector_t& v1, const Vector_t& v2)
{
	Vector_t v(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
	return v;
}

Vector_t operator-(const Vector_t& v1, const Vector_t& v2)
{
	Vector_t v(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
	return v;
}

Vector_t operator*(double v, const Vector_t& v2)
{
	Vector_t u(v*v2.x, v*v2.y, v*v2.z);
	return u;
}

Vector_t operator*(const Vector_t& v1, double v)
{
	Vector_t u(v*v1.x, v*v1.y, v*v1.z);
	return u;
}

double operator*(const Vector_t& v1, const Vector_t& v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Vector_t operator^(const Vector_t& v1, const Vector_t& v2)
{
	Vector_t u(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
	return u;
}

bool operator==(const Vector_t& v1, const Vector_t& v2)
{
	return v1.x==v2.x && v1.y==v2.y && v1.z==v2.z;
}

bool operator!=(const Vector_t& v1, const Vector_t& v2)
{
	return !(v1==v2);
}

Vector_t operator/(const Vector_t& v, double s)
{
	Vector_t u((v.x)/s, (v.y)/s, (v.z)/s);
	return u;
}

ostream& operator<<(ostream& out, const Vector_t& v)
{
	out<<"["<<v.x<<","<<v.y<<","<<v.z<<"]";
	return out;
}
#endif
