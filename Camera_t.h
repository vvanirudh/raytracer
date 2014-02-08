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

	void render(Scene_t s, int h, int w, Color_t** finalColor)
	{
		Ray_t cameraRay(pos);

		for(int x = -h/2; x<h/2; x++)
		{
			for(int y = -w/2;y<w/2; y++)
			{
				finalColor[x][y].setColor(0,0,0);
				s.releaseRay(&cameraRay,x,y);
				finalColor[x][y].setColor(computeColor(cameraRay, 0, s));
			}
		}
	}
};

#endif