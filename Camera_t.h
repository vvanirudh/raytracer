#ifndef CAMERA_T_H_
#define CAMERA_T_H_

#include "globals.h"
#include "Point_t.h"
#include "Scene_t.h"
#include "Color_t.h"
#include "Ray_t.h"

class Camera_t
{
public:
	Point_t pos;
	Point_t lookAt;
	Point_t up;

	Camera_t(Point_t p, Point_t l, Point_t u)
	{
		pos = p;
		lookAt = l;
		up = u;
	}

	void render(Scene_t s, int h, int w, Color_t** finalColor, int depth)
	{
		Ray_t cameraRay(pos);

		for(int x = -h/2; x<h/2; x++)
		{
			for(int y = -w/2;y<w/2; y++)
			{
				finalColor[x][y].setColor(0,0,0);
				s.releaseRay(&cameraRay,x,y);
				finalColor[x][y].setColor(computeColor(cameraRay, depth, s));
			}
		}
	}

	Color_t computeColor(Ray_t r, int depth, Scene_t s)
	{
		Color_t pixelColor;
		list<Object_t*>::iterator objItr;
		bool intersectRay = false;
		Object_t * obj;
		Point_t tempInt;
		Point_t finalInt;
		double tempDist = 0.0;
		double finalDist = 1000000.0;
		bool shadow = false;
		double shadowDist;

		for(objItr = s.Objects.begin(); objItr!=s.Objects.end(); ++objItr)
		{
			intersectRay = (*objItr)->intersect(r, &tempDist, &tempInt);
			if(intersectRay)
			{
				if(tempInt != r.org)
				{
					shadow = true;
					if(abs(tempDist) < finalDist)
					{
						finalDist = abs(tempDist);
						finalInt = tempInt;
						obj = *objItr;
					}
				}
			}
		}

		if(shadow)
		{
			Data data;

			intersectRay = false;
			tempDist = 0.0;
			finalDist = 1000000.0;

			bool inShadow = false;

			
		}
	}
};

#endif