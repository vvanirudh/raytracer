#ifndef CYLINDER_T_H
#define CYLINDER_T_H 

#include "Object_t.h"
#include <cmath>

class Cylinder_t : public virtual Object_t
{
public:
	Point_t baseCenter;
	double baseRadius;
	double height;
	Vector_t axis;

	Cylinder_t(Point_t center, double baseR, double h, Vector_t ax)
	{
		baseCenter = center;
		baseRadius = baseR;
		height = h;
		axis = ax;
	}

	bool intersect(Ray_t ray, double* dist, Point_t* intPoint)
	{
		bool hit;
		Vector_t RC = baseCenter - ray.org;

		double d;
		double t,s;
		Vector_t D, O;
		double h1, h2;

		Vector_t n = ray.dir ^ axis;

		double l = n.length();
		
		n.normalizeVector();
		d = abs(RC*n);
		hit = (d<=baseRadius);

		if(hit)
		{
			O = RC ^ axis;
			t = -1* (O*n)/l;
			O = n ^ axis;
			O.normalizeVector();
			s = abs(sqrt(baseRadius*baseRadius - d*d));
			h1 = t - s;
			h2 = t + s;
		}
		
		*dist = h1;
		return hit;

	}

	Vector_t getNormal(Point_t)
	{
		
	}

	/* http://tog.acm.org/resources/GraphicsGems/gemsiv/ray_cyl.c */
};

#endif