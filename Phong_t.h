#ifndef PHONG_T_H_
#define PHONG_T_H_ 

#include "Point_t.h"
#include "Vector_t.h"
#include "Lightsrc_t.h"
#include <cmath>
#include <vector>

using namespace std;

struct Data
{
public:
	Point_t point;
	Vector_t normal;
	Ray_t viewRay;
	Ray_t inRay;
	Ray_t refRay;
	Lightsrc_t * lSrc; 

	Data()
	{
		
	}

	Data(const Data& d)
	{
		point = d.point;
		normal = d.normal;
		viewRay = d.viewRay;
		inRay = d.inRay;
		refRay = d.refRay;
		lSrc = d.lSrc;
	}
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
		ka = a;
		kd = d;
		ks = s;
		n = e;
	}


	void illuminate(vector<Data> vec, Color_t ambient, Color_t diffuse, Color_t specular, Color_t objColor)
    {
        //SPECULAR COMPONENT

    	// cout<<ambient<<endl;
    	// cout<<diffuse<<endl;
    	// cout<<specular<<endl;


        ambColor.setColor(ka * ambient.r * objColor.r , ka * ambient.g * objColor.g , ka * ambient.b * objColor.b );

        double ac_dr = 0,ac_dg = 0,ac_db = 0,ac_sr = 0,ac_sg = 0,ac_sb = 0;
        int nData = vec.size();
        for (int i = 0; i < nData; ++i)
        {
            
        // DIFFUSE COMPONENT
        double d = vec[i].inRay.dir * vec[i].normal;
        // cout<<"d value: "<<d<<endl;
        Color_t lColor;
        lColor = vec[i].lSrc->getColor();
        ac_dr = ac_dr + (lColor.r * (diffuse.r) * d);
        ac_dg = ac_dg + (lColor.g * (diffuse.g) * d);
        ac_db = ac_db + (lColor.b * (diffuse.b) * d); 
        //Color_t diffuseColor(lColor.r * (diffuse.r) * d , lColor.g * (diffuse.g) * d , lColor.b * (diffuse.b) * d);

        //SPECULAR COMPONENT
        double e = vec[i].refRay.dir * vec[i].viewRay.dir;
        e = pow(e, n);
        ac_sr = ac_sr + (lColor.r * (specular.r) * e);
        ac_sg = ac_sg + (lColor.g * (specular.g) * e);
        ac_sb = ac_sb + (lColor.b * (specular.b) * e);
        //Color_t specularColor(lColor.r * (specular.r) * e, lColor.g * (specular.g) * e, lColor.b * (specular.b) * e);
        }
        //FINAL COLOR
        color.setColor(ka * ambColor.r + kd * ac_dr + ks * ac_sr,
                        ka * ambColor.g + kd * ac_dg + ks * ac_sg,
                        ka * ambColor.b + kd * ac_db + ks * ac_sb);

        // cout<<"Final Color: "<<color;
    }

	void illuminateAmbient(Color_t ambient, Color_t diffuse)
	{
		color.setColor(ka*ambient.r*diffuse.r,
						ka*ambient.g*diffuse.g,
						ka*ambient.b*diffuse.b);
		// cout<<color;
	}

};

#endif