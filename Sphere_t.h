#ifndef SPHERE_T_H
#define SPHERE_T_H

#include "Object_t.h"

class Sphere : public virtual Object_t
{
public:
	Point_t center;
	double radius;

	Sphere(Point_t, double);
	bool intersect(Ray_t, double*, Point_t*);

	Vector_t getNormal(Point_t);

};

#endif