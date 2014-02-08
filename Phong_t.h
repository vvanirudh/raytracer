#ifndef PHONG_T_H_
#define PHONG_T_H_ 

#include "Point_t.h"
#include "Vector_t.h"
#include "Lightsrc_t.h"
#include <cmath>

struct Data
{
public:
	Point_t point;
	Vector_t normal;
	Ray_t viewRay;
	Ray_t inRay;
	Ray_t refRay;
	Lightsrc_t * lSrc; 
};

class Phong_t
{
public:
	double ka, kd, ks;
	double n;
	Color_t ambColor;
	Color_t color;

	Phong_t()
	{

	}

	Phong_t(double amb, double dif, double spec, double exponent)
	{
		ka = amb;
		kd = dif;
		ks = spec;
		n = exponent;
	}


	void setCoeff(double a, double d, double s, double e)
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
		Color_t lColor = data.lSrc->getColor();

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

	void illuminate(vector<Data> vec, Color_t ambient, Color_t diffuse, Color_t specular, Color_t objColor)
    {
        //SPECULAR COMPONENT
        ambColor.setColor(ka * ambient.r * objColor.r , ka * ambient.g * objColor.g , ka * ambient.b * objColor.b );

        double ac_dr = 0,ac_dg = 0,ac_db = 0,ac_sr = 0,ac_sg = 0,ac_sb = 0;
        for (vector<>::iterator i = vec.begin(); i != vec.end(); ++i)
        {
            
        // DIFFUSE COMPONENT
        double d = i->inRay.dir * i->normal;
        Color_t lColor = i->lSrc->getColor();
        ac_dr = ac_dr + (lColor.r * (diffuse.r) * d);
        ac_dg = ac_dg + (lColor.g * (diffuse.g) * d);
        ac_db = ac_db + (lColor.b * (diffuse.b) * d); 
        //Color_t diffuseColor(lColor.r * (diffuse.r) * d , lColor.g * (diffuse.g) * d , lColor.b * (diffuse.b) * d);

        //SPECULAR COMPONENT
        double e = i->refRay.dir * i->viewRay.dir;
        e = pow(e, n);
        ac_sr = ac_sr + (lColor.r * (specular.r) * e);
        ac_sg = ac_sg + (lColor.g * (specular.g) * d);
        ac_sb = ac_sb + (lColor.b * (specular.b) * d);
        //Color_t specularColor(lColor.r * (specular.r) * e, lColor.g * (specular.g) * e, lColor.b * (specular.b) * e);
        }
        //FINAL COLOR
        color.setColor(ka * ambColor.r + kd * ac_dr + ks * ac_sr,
                        ka * ambColor.g + kd * ac_dg + ks * ac_sg,
                        ka * ambColor.b + kd * ac_db + ks * ac_sb);
    }

	void illuminateAmbient(Color_t ambient, Color_t diffuse)
	{
		color.setColor(ka*ambient.r*diffuse.r,
						ka*ambient.g*diffuse.g,
						ka*ambient.b*diffuse.b);
	}

};

#endif