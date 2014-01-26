#ifndef OBJECT_T_H
#define OBJECT_T_H

#include "Vector_t.h"
#include "Point_t.h"
#include "color_t.h"
#include "ray_t.h"

class Object_t
{
public:
	Vector_t normal;

	Color_t diffuseColor, specularColor;

	double reflectance, transmittance;

	void setDiffColor(Color_t a)
	{
		diffuseColor = a;
	}

	void setSpecColor(Color_t a)
	{
		specularColor = a;
	}

	void setReflectance(double a)
	{
		reflectance = a;
	}

	void setTransmittance(double a)
	{
		transmittance = a;
	}

	virtual bool intersect(Ray_t r, double* distance, Point_t* pointOfIntersection);

	virtual Vector_t getNormal(Point_t);
};

#endif