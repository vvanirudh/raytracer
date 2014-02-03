#ifndef CYLINDER_T_H
#define CYLINDER_T_H 

#include "Object_t.h"

class Cylinder_t : public virtual Object_t
{
public:
	Point_t baseCenter;
	double baseRadius;
	double topRadius;
	double height;

	Cylinder_t(Point_t, double, double, double);
	bool intersect(Ray_t, double*, Point_t*);
	Vector_t getNormal(Point_t);

	/* http://tog.acm.org/resources/GraphicsGems/gemsiv/ray_cyl.c */
};

#endif