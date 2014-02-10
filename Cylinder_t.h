#ifndef CYLINDER_T_H
#define CYLINDER_T_H 

#include "Object_t.h"
#include <cmath>

class Cylinder_t : public virtual Object_t
{
public:
	Point_t baseCenter;
	double baseRadius;
	double height;
	Vector_t axis;
	Point_t topCenter;

	Cylinder_t(Point_t center, double baseR, double h, Vector_t ax)
	{
		baseCenter = center;
		baseRadius = baseR;
		height = h;
		axis = ax;
		axis.normalizeVector();
		topCenter = center +  h*ax;
	}

	Cylinder_t(const Cylinder_t& c)
	{
		baseCenter = c.baseCenter;
		baseRadius = c.baseRadius;
		height = c.height;
		axis = c.axis;
		topCenter = c.topCenter;
		phong = c.phong;
		diffuseColor = c.diffuseColor;
		specularColor = c.specularColor;
		reflectance = c.reflectance;
		transmittance = c.transmittance;
		refIndex = c.refIndex;
	}

	bool intersect(Ray_t ray, double* dist, Point_t* intPoint)
	{
		Vector_t delta_p;
		delta_p = ray.org - baseCenter;

		Vector_t v_form;
		v_form = ray.dir - (ray.dir * axis)*axis;
		Vector_t p_form;
		p_form = delta_p - (delta_p * axis)*axis;

		double A = v_form * v_form;
		double B = 2* (v_form * p_form);
		double C = (p_form * p_form) - (baseRadius * baseRadius);

		double D = B*B - 4*A*C;


		if(D<0)
		{
			return false;
		}
		else
		{
			double d1 = -(-B - sqrt(D))/2.0*A;
			double d2 = -(-B + sqrt(D))/2.0*A;

			Point_t p1;
			p1 = ray.org + d1*ray.dir;
			Point_t p2;
			p2 = ray.org + d2*ray.dir;

			Vector_t v1;
			// v1 = topCenter - p1;
			v1 = p1 - topCenter;
			Vector_t v2;
			// v2 = baseCenter - p1;
			v2 = p1 - baseCenter;

			Vector_t v3;
			// v3 = topCenter - p2;
			v3 = p2 - topCenter;
			Vector_t v4;
			// v4 = baseCenter - p2;
			v4 = p2 - baseCenter;			

			double dot11 = axis * v2;
			double dot12 = axis * v1;

			double dot21 = axis * v4;
			double dot22 = axis * v3;

			vector<double> distances;
			if((dot11 > 0) && (dot12 < 0))
			{
				if((dot21 > 0) && (dot22 < 0))
				{
					if(abs(d1) < abs(d2))
					{
						*intPoint = p1;
						*dist = d1;
						// cout<<"1 d1 : "<<d1<<endl;

						return true;
					}
					else
					{
						*intPoint = p2;
						*dist = d2;
						// cout<<" d2 : "<<d2<<endl;

						return true;
					}

					// distances.push_back(d1);
					// distances.push_back(d2);
				}
				else
				{
					*intPoint = p1;
					*dist = d1;
					// cout<<"3 d1 : "<<d1<<endl;

					return true;

					// distances.push_back(d1)
				}
			}
			else if((dot21 > 0) && (dot22 < 0))
			{
				*intPoint = p2;
				*dist = d2;
				// cout<<" d2 : "<<d2<<endl;

				return true;
				// distances.push_back(d2);

			}




			return false;
		}
	}

	Vector_t getNormal(Point_t t)
	{
		Vector_t v;
		v = t - baseCenter;
		double d = v * axis;
		Point_t p;
		p = baseCenter + d*axis;
		Vector_t norm;
		norm = t - p;
		return norm;
	}

	/* http://tog.acm.org/resources/GraphicsGems/gemsiv/ray_cyl.c */
};

#endif