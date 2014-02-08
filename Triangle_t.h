#ifndef TRIANGLE_T
#define TRIANGLE_T

#include "Object_t.h"

class Triangle_t : public virtual Object_t
{
public:
	Point_t v[3];

	//Default Constructor
	Triangle_t(Point_t a1, Point_t a2, Point_t a3)
	{
		v[0] = a1;
		v[1] = a2;
		v[2] = a3;

		// Since the triangle is a planar surface, the normal is same at every point. So let's create the 
		// normal in the constructor itself

		Vector_t side1;
		side1 = v[0]-v[1];
		side1.normalizeVector();
		Vector_t side2;
		side2 = v[1]-v[2];
		side2.normalizeVector();

		normal = side1 ^ side2; //Cross product of sides of the triangle gives us the normal for the triangle
		normal.normalizeVector();

	}

	Vector_t getNormal(Point_t t)
	{
		return normal;
	}

	bool intersect(Ray_t r, double* d, Point_t* point)
	{
		/* The following algorithm is called 'Moller-Trumbore intersection algorithm', the information is taken
		from Wikipedia */

		Vector_t side1;
		side1 = v[1]-v[0];
		Vector_t side2;
		side2 = v[2]-v[0];

		Vector_t p;
		p = r.dir ^ side2;
		double det = side1 * p;

		if((det > -0.0001) && (det < 0.0001))
			return false;

		double inv_det = 1/det;

		Vector_t T;
		T = r.org - v[0];

		double u = (T * p) * inv_det;

		if(u<0 || u>1)
			return false;

		Vector_t Q;
		Q = T ^ side1;
		double v_t = (r.dir * Q) * inv_det;

		if(v_t<0 || u+v_t>1)
			return false;

		double t = (side2 * Q) * inv_det;

		if(t>0.0001)
		{
			(*point) = (1-u-v_t)*v[0] + u*v[1] + v_t*v[1];
			*d = t;
			return true;
		}

		return false;

		/* http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-9-ray-triangle-intersection/m-ller-trumbore-algorithm/ 
		/* Need to understand the algorithm */
		
	}
	//Destructor
	//~Triangle_t()

	/* data */
};
#endif