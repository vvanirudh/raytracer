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

		bool val = false;
		double ndist,odist;
		
		if(D>0){
			d1 = (-b - sqrt(D))/2.0;
			d2 = (-b + sqrt(D))/2.0;

			
			if(abs(d1) > abs(d2))
			{
				*d = d2;
				odist = d1;
				ndist = d2;
			}
			else
			{
				*d = d1;
				odist = d2;
				ndist = d1;
			}

			if(abs(*d)>0.75)
				val = true;
		}
		else if(D==0)
		{
			*d = -b/2;
			if(abs(*d)>0.75)
				val = true;
		}

		if(val){
			(*P).x = r.org.x + (r.dir.x)*(*d);
			(*P).y = r.org.y + (r.dir.y)*(*d);
			(*P).z = r.org.z + (r.dir.z)*(*d);


			if(*P == r.org || (abs(((*P).x) - r.org.x) < 0.01 && abs(((*P).y) - r.org.y) < 0.01 && abs(((*P).z) - r.org.z) < 0.01))
			{
				// cout<<"MACHAXX\n";
				// *d = odist;
				// (*P).x = r.org.x + (r.dir.x)*(*d);
				// (*P).y = r.org.y + (r.dir.y)*(*d);
				// (*P).z = r.org.z + (r.dir.z)*(*d);
				val = false;
			}
		}

		Vector_t vec;
		vec = *P - r.org;
		double ret = vec * r.dir;
		if(ret>0)
			val = false;

		return val;
	}

	Vector_t getNormal(Point_t p)
	{
		normal = p - center;
		normal.normalizeVector();//dunno about this normalize()
		return normal;
	}

};

#endif
