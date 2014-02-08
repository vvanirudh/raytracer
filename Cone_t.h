#ifndef CONE_T_H
#define CONE_T_H 

#include "Object_t.h"

class Cone_t : public virtual Object_t
{
public:
	Point_t baseCenter;
	double baseRadius;
	double height;
	Vector_t axis;
	Cylinder_t(Point_t, double, double, Vector_t);
	bool intersect(Ray_t, double*, Point_t*);
	Vector_t getNormal(Point_t);

	/* http://tog.acm.org/resources/GraphicsGems/gemsiv/ray_cyl.c */
};

#endif