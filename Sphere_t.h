#ifndef SPHERE_T_H
#define SPHERE_T_H

#include "Object_t.h"

class Sphere_t : public virtual Object_t
{
public:
	Point_t center;
	double radius;

	Sphere_t(Point_t c, double r)
	{
		center = c;
		radius = r;
	}

	bool intersect(Ray_t r, double* d, Point_t *P)//have to check some vector and point related issues
	{
		double a,b,c,D,q,d1,d2,temp; //a,b,c are the coefficients of equation 
		a = r.dir*r.dir;
		b = 2*(r.org - center)*(r.dir);
		c = (r.org - center)*(r.org -center) - radius*radius;
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

		(*P).x = r.org.x + (r.dir.x)*(*d);
		(*P).y = r.org.y + (r.dir.y)*(*d);
		(*P).z = r.org.z + (r.dir.z)*(*d);


		if(*P == r.org)
		{
			*d = dist;
			(*P).x = r.org.x + (r.dir.x)*(*d);
			(*P).y = r.org.y + (r.dir.y)*(*d);
			(*P).z = r.org.z + (r.dir.z)*(*d);
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
