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

	Point_t& operator=(const Point_t& a)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		return *this;
	}


	double distanceBetween(Point_t& p)
	{
		double d = sqrt((p.x-x)*(p.x-x) + (p.y-y)*(p.y-y) + (p.z-z)*(p.z-z));
		return d;
	}

};

#endif	