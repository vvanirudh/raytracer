#ifndef OBJECT_T_H
#define OBJECT_T_H

#include "Vector_t.h"
#include "Point_t.h"
#include "color_t.h"

class Object_t
{
public:
	Vector_t normal;

	Color_t diffuseColor, specularColor;

	double reflectance, transmittance;
};

#endif