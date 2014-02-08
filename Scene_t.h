#ifndef SCENE_T_H_
#define SCENE_T_H_

#include "Object_t.h"
#include <list>
#include "Lightsrc_t.h"
#include "Ray_t.h"
#include "Point_t.h"

class Scene_t
{
public:
	double nearPlane;
	double scaleFactor;

	list<Object_t*> Objects;
	list<Lightsrc_t*> Lights;

	Scene_t()
	{
		
	}

	Scene_t(double n, double s)
	{
		nearPlane = n;
		scaleFactor = s;
	}

	~Scene_t()
	{
		
	}

	void add(Object_t* o)
	{
		Objects.push_back(o);
	}

	void add(Lightsrc_t* l)
	{
		Lights.push_back(l);
	}

	void releaseRay(Ray_t* r, double x, double y)
	{
		Point_t p(scaleFactor*x, -1*scaleFactor*y, -1*scaleFactor*nearPlane);
		Vector_t direction = (*r).org - p;
		direction.normalizeVector();
		(*r).dir = direction;
	}

	void releaseShadowRay(Ray_t* r, Point_t* p)
	{
		Vector_t direction = (*r).org - *p;
		direction.normalizeVector();
		(*r).dir = direction;
	}
};

#endif