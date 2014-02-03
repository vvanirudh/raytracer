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

	bool intersect(Ray_t r, double* d, Point_t *P);//have to check some vector and point related issues
	{
		double a,b,c,D,q,d1,d2,temp; //a,b,c are the coefficients of equation 
		a = r.v*r.v;
		b = 2*(r.p - center)*(r.v);
		c = (r.p - center)*(r.p -center) - radius*radius;
		D = b*b - 4*a*c;

		if(D < 0)
			return false;

		double dist;

		d1 = (-b - sqrt(D))/2.0;
		d2 = (-b + sqrt(D))/2.0;
		
		if(abs(d1) > abs(d2))
		{
			*d = d2;
			dist = d1;
		}
		else
		{
			*d = d1;
			dist = d2;
		}

		*P = r.org + (r.dir)*(*d);
		if(*P == r.org)
		{
			*d = dist;
			*P = r.org + (r.dir)*(*d);
		}

		return true;
	}

	Vector_t getNormal(Point_t p)
	{
		normal = p - center;
		normal.normalizeVector();//dunno about this normalize()
		return normal;
	}

};

#endif
