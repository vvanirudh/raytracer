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

	// color_t getColor() const
	// {
	// 	return diffuseColor;
	// }

	// Point_t getCenter() const
	// {
	// 	return center;
	// }


	bool intersect(Ray_t, double*, Point_t*);

	Vector_t getNormal(Point_t p)
	{
		normal = p - center;
		normal.normalize();//dunno about this normalize()
		return normal;
	}

};

#endif