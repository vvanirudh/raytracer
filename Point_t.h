#ifndef _POINT_T_H_
#define _POINT_T_H_

#include <cmath>
#include <iostream>
#include "Vector_t.h"

using namespace std;	

class Point_t
{
public:
	double x,y,z;

	Point_t()
	{
		
	}

	Point_t(double xx, double yy, double zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}

	Point_t(Point_t& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
	}

	Point_t& operator=(const Point_t& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		return *this;
	}

	Point_t& operator+=(const Vector_t& a)
	{
		x+=a.x;
		y+=a.y;
		z+=a.z;
		return *this;
	}

	Point_t& operator*=(double s)
	{
		x*=s;
		y*=s;
		z*=s;
		return *this;
	}

	double distanceBetween(Point_t& p)
	{
		double d = sqrt((p.x-x)*(p.x-x) + (p.y-y)*(p.y-y) + (p.z-z)*(p.z-z));
		return d;
	}

};

Vector_t operator-(const Point_t& p1, const Point_t& p2)
{
	Vector_t u(p1.x-p2.x, p1.y-p2.y, p1.z-p2.z);
	return u;
}

Point_t operator+(const Point_t& p1, const Point_t& p2)
{
	Point_t u(p1.x+p2.x, p1.y+p2.y, p1.z+p2.z);
	return u;
}

Point_t operator*(double v, const Point_t& p)
{
	Point_t u(v*p.x, v*p.y, v*p.z);
	return u;
}

Point_t operator*(const Point_t& p, double v)
{
	Point_t u(v*p.x, v*p.y, v*p.z);
	return u;
}

bool operator==(const Point_t& p1, const Point_t& p2)
{
	return p1.x==p2.x && p1.y==p2.y && p1.z==p2.z;
}

bool operator!=(const Point_t& p1, const Point_t& p2)
{
	return !(p1==p2);
}

Point_t operator+(const Point_t & p1, const Vector_t& v)
{
	Point_t u(p1.x+v.x, p1.y+v.y, p1.z*v.z);
	return u;
}

Point_t operator+(const Vector_t& v, const Point_t & p1)
{
	Point_t u(p1.x+v.x, p1.y+v.y, p1.z*v.z);
	return u;
}

ostream& operator<<(ostream& out, const Point_t& p)
{
	out<<"("<<p.x<<","<<p.y<<","<<p.z<<")";
	return out;
}

#endif	