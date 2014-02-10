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
		side1 = v[1]-v[0];
		side1.normalizeVector();
		Vector_t side2;
		side2 = v[2]-v[0];
		side2.normalizeVector();

		normal = side1 ^ side2; //Cross product of sides of the triangle gives us the normal for the triangle
		normal.normalizeVector();
		normal = -normal;

	}

	Triangle_t(const Triangle_t& s)
	{
		v[0] = s.v[0];
		v[1] = s.v[1];
		v[2] = s.v[2];
		normal = s.normal;
		phong = s.phong;
		diffuseColor = s.diffuseColor;
		specularColor = s.specularColor;
		reflectance = s.reflectance;
		transmittance = s.transmittance;
		refIndex = s.refIndex;
	}

	Vector_t getNormal(Point_t t)
	{
		return normal;
	}

	bool intersect(Ray_t r, double* d, Point_t* point)
	{
		/* The following algorithm is called 'Moller-Trumbore intersection algorithm', the information is taken
		from Wikipedia */
		// cout<<"lol\n";
		Vector_t side1;
		side1 = v[1]-v[0];
		Vector_t side2;
		side2 = v[2]-v[0];

		Vector_t p;
		p = r.dir ^ side2;
		double det = side1 * p;

		if((det > -0.0001) && (det < 0.0001))
			return false;

		double inv_det = 1.0/det;

		Vector_t T;
		T = r.org - v[0];

		double u = inv_det * (T * p);

		if(u<0 || u>1)
			return false;

		Vector_t Q;
		Q = T ^ side1;
		double v_t = inv_det * (r.dir * Q);

		if(v_t<0 || u+v_t>1)
			return false;

		double t = inv_det * (side2 * Q) ;
		
		// cout<<t<<endl;
		// if(t>0.01)
		// {
			(*point) = (1-u-v_t)*v[0] + u*v[1] + v_t*v[1];
			*d = t;
			return true;
		// }

		// return false;

		/* http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-9-ray-triangle-intersection/m-ller-trumbore-algorithm/ 
		/* Need to understand the algorithm */
		
	}

// 	intersect_triangle(double orig[3], double dir[3],
//                    double vert0[3], double vert1[3], double vert2[3],
//                    double *t, double *u, double *v)
// {
//    double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
//    double det,inv_det;

//    /* find vectors for two edges sharing vert0 */
//    SUB(edge1, vert1, vert0);
//    SUB(edge2, vert2, vert0);

//    /* begin calculating determinant - also used to calculate U parameter */
//    CROSS(pvec, dir, edge2);

//    /* if determinant is near zero, ray lies in plane of triangle */
//    det = DOT(edge1, pvec);

// #ifdef TEST_CULL           /* define TEST_CULL if culling is desired */
//    if (det < EPSILON)
//       return 0;

//    /* calculate distance from vert0 to ray origin */
//    SUB(tvec, orig, vert0);

//    /* calculate U parameter and test bounds */
//    *u = DOT(tvec, pvec);
//    if (*u < 0.0 || *u > det)
//       return 0;

//    /* prepare to test V parameter */
//    CROSS(qvec, tvec, edge1);

//      calculate V parameter and test bounds 
//    *v = DOT(dir, qvec);
//    if (*v < 0.0 || *u + *v > det)
//       return 0;

//    /* calculate t, scale parameters, ray intersects triangle */
//    *t = DOT(edge2, qvec);
//    inv_det = 1.0 / det;
//    *t *= inv_det;
//    *u *= inv_det;
//    *v *= inv_det;
// #else                    /* the non-culling branch */
//    if (det > -EPSILON && det < EPSILON)
//      return 0;
//    inv_det = 1.0 / det;

//    /* calculate distance from vert0 to ray origin */
//    SUB(tvec, orig, vert0);

//    /* calculate U parameter and test bounds */
//    *u = DOT(tvec, pvec) * inv_det;
//    if (*u < 0.0 || *u > 1.0)
//      return 0;

//    /* prepare to test V parameter */
//    CROSS(qvec, tvec, edge1);

//    /* calculate V parameter and test bounds */
//    *v = DOT(dir, qvec) * inv_det;
//    if (*v < 0.0 || *u + *v > 1.0)
//      return 0;

//    /* calculate t, ray intersects triangle */
//    *t = DOT(edge2, qvec) * inv_det;

//    cout<<"t: "<<*t<<endl;
// #endif
//    return 1;
// }
	
};
#endif