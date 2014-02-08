#ifndef OBJECT_T_H
#define OBJECT_T_H

#include "Vector_t.h"
#include "Point_t.h"
#include "color_t.h"
#include "ray_t.h"
#include "Phong_t.h"

class Object_t
{
public:
	Vector_t normal;

	Color_t diffuseColor, specularColor;

	Phong_t * phong;

	double reflectance, transmittance, refIndex;

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

	void setRefIndex(double r)
	{
		refIndex = r;
	}

	Color_t getColor()
	{
		return diffuseColor;
	}

	void setPhong(Phong_t p)
	{
		*phong = p;
	}

	void setMaterial(Color diff, Color spec, double ambCoeff, double diffCoeff, double specCoeff, double exponent)
	{
		diffuseColor = diff; specularColor = spec;
		phong->setCoeff(ambCoeff, diffCoeff, specCoeff, exponent);
	}

	virtual bool intersect(Ray_t r, double* distance, Point_t* pointOfIntersection) = 0;
	// These two functions are abstract functions needed to be defined in the subclasses of the class Object_t.h
	virtual Vector_t getNormal(Point_t) = 0;
};

#endif