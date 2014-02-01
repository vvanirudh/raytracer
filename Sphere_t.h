#ifndef SPHERE_T_H
#define SPHERE_T_H

#include "Object_t.h"

class Sphere : public virtual Object_t
{
public:
	Point_t center;
	double radius;

	Sphere(Point_t c, double r)
	{
		center = c;
		radius = r;
	}

	bool intersect(Ray_t r, Point_t P);//have to check some vector and point related issues
	{
		double a,b,c,D,q,d1,d2,temp; //a,b,c are the coefficients of equation 
		a = r.v*r.v;
		b = 2*(r.p - center)*(r.v);
		c = (r.p - center)*(r.p -center) - radius*radius;
		D = b*b - 4*a*c;
		if(D < 0)
			return false;
		d1 = (-b - sqrt(D))/2.0;
		d2 = (-b + sqrt(D))/2.0;
		
		if(abs(d1) > abs(d2))
		{
			temp = d2;
			d2   = d1;
			d1   = temp;
		}
		P = r.p + (r.v)*(d1);
	}

	// Point_t intersect_point(Ray_t);
	// {

	// }

	Vector_t getNormal(Point_t p)
	{
		normal = p - center;
		normal.normalize();//dunno about this normalize()
		return normal;
	}

};

#endif