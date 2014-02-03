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

	Color_t getColor()
	{
		return diffuseColor;
	}

	virtual bool intersect(Ray_t r, double* distance, Point_t* pointOfIntersection) = 0;
	// These two functions are abstract functions needed to be defined in the subclasses of the class Object_t.h
	virtual Vector_t getNormal(Point_t) = 0;
};

#endif