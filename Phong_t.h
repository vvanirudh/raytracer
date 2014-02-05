#ifndef PHONG_T_H_
#define PHONG_T_H_ 

#include "Point_t.h"
#include "Vector_t.h"
#include "Lightsrc_t.h"
#include "<cmath>"

struct Data
{
public:
	Point_t point;
	Vector_t normal;
	Ray_t viewRay;
	Ray_t inRay;
	Ray_t refRay;
	Lightsrc_t lSrc; 
};

class Phong_t
{
public:
	double ka, kd, ks;
	double n;
	Color_t ambColor;
	Color_t color;

	Phong_t(double amb, double dif, double spec, double exponent)
	{
		ka = amb;
		kd = dif;
		ks = spec;
		n = exponent;
	}

	void illuminate(Data data, Color_t ambient, Color_t diffuse, Color_t specular, Color_t objColor)
	{
		//SPECULAR COMPONENT
		ambColor.setColor(ka * ambient.r * objColor.r , ka * ambient.g * objColor.g , ka * ambient.b * objColor.b );

		// DIFFUSE COMPONENT
		double d = data.inRay.dir * data.normal;
		Color_t lColor = data.lSrc.getColor();

		Color_t diffuseColor(lColor.r * (diffuse.r) * d , lColor.g * (diffuse.g) * d , lColor.b * (diffuse.b) * d);

		//SPECULAR COMPONENT
		double e = data.refRay.dir * data.viewRay.dir;
		e = pow(e, n);

		Color_t specularColor(lColor.r * (specular.r) * e, lColor.g * (specular.g) * e, lColor.b * (specular.b) * e);

		//FINAL COLOR
		color.setColor(ka * ambColor.r + kd * diffuseColor.r + ks * specularColor.r,
						ka * ambColor.g + kd * diffuseColor.g + ks * specularColor.g,
						ka * ambColor.b + kd * diffuseColor.b + ks * specularColor.b);
	}

};

#endif