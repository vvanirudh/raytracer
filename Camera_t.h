#ifndef CAMERA_T_H_
#define CAMERA_T_H_

#include "globals.h"
#include "Point_t.h"
#include "Scene_t.h"
#include "color_t.h"
#include "ray_t.h"
#include "Object_t.h"
#include <cstdlib>
#include <cmath>

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
		Color_t ambientColor(1,1,1);
		depth++;
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
			vector<Data> dataVec;

			intersectRay = false;
			tempDist = 0.0;
			finalDist = 1000000.0;

			bool inShadow = false;

			list<Lightsrc_t*>::iterator lightItr;

			for(lightItr = s.Lights.begin(); lightItr!=s.Lights.end(); ++lightItr)
			{
				Ray_t shadowray((*lightItr)->getpos());

				s.releaseShadowRay(&shadowray, &finalInt);
				Object_t * objRef;

				shadowDist = shadowray.org.distanceBetween(finalInt);

				shadowDist = shadowDist - 0.000001;

				for(objItr = s.Objects.begin();objItr!=s.Objects.end();++objItr)
				{
					intersectRay = (*objItr)->intersect(shadowray, &tempDist, &tempInt);

					if(intersectRay)
					{
						if(tempInt!=finalInt)
						{
							if(abs(tempDist)< finalDist)
							{
								finalDist = abs(tempInt);
								objRef = *objItr;
							}

							/*** inShadow code **/
						}
					}
				}

				Data data;
				data.lSrc = (*lightItr);
				data.inRay = shadowray;
				data.normal = obj->getNormal(objInt);

				Ray_t viewRay(objInt);

				Vector_t viewVec = r.org - objInt;
				viewVec.normalizeVector();
				viewRay.setDirection(viewVec);
				data.viewRay = viewRay;
				data.point = objInt;

				Ray_t refRay(objInt);
				Vector_t refDir = 2*((shadowray.dir * data.normal) * (data.normal)) - (shadowray.dir);
				refDir.normalizeVector();
				refRay.setDirection(refDir);
				data.refRay = refRay;

				dataVec.push_back(data);
			}


			if(finalDist > shadowDist)
			{
				obj->phong->illuminate(dataVec, ambientColor, obj->diffuseColor, obj->specularColor);
				// obj->phong->illuminate()
			}
			else
			{
				obj->phong->illuminateAmbient(ambientColor, obj->diffuseColor);
			}

			pixelColor = obj->phong->color;

			if(depth < DEPTH)
			{
				Color_t refColor;

				if((obj->reflectance) > 0.0)
				{
					Ray_t reflRay(objInt);
					Vector_t reflDir = r.dir - 2*(r.dir*data.normal)*(data.normal);
					reflDir.normalizeVector();
					reflRay.setDirection(reflDir);

					double reflectance = obj->reflectance;

					refColor.setColor(computeColor(reflRay, depth, s));
					pixelColor.r += reflectance * refColor.r;
					pixelColor.b += reflectance * refColor.b;
					pixelColor.g += reflectance * refColor.g;
				}

				if((obj->transmittance) > 0.0)
				{
					Ray_t transmitRay(objInt);
					Vector_t normal = -data.normal;
					double transmittance = obj->transmittance;
					double refIndex = obj->refIndex;
					double n = 1/(refIndex);

					if((data.normal * r.dir)<0)
					{
						normal = -normal;
						n = 1/n;
					}

					/** Can check for TIR if we want **/
					double tir = sqrt( 1 + (n*n)*(((-(r.dir)*normal)*(-(r.dir)*normal)) - 1));

					if(tir<0)
					{
						pixelColor.r += transmittance * refColor.r;
						pixelColor.b += transmittance * refColor.b;
						pixelColor.g += transmittance * refColor.g;
					}
					else{
						Vector_t transmitDir = (n * r.dir) + (n * (-(r.dir) * normal) -  tir) * normal;
						transmitDir.normalizeVector();
						transmitRay.setDirection(transmitDir);
						Color_t transmitColor;
						transmitColor.setColor(computeColor(transmitRay, depth, s));
						pixelColor.r += transmittance * transmitColor.r;
						pixelColor.b += transmittance * transmitColor.b;
						pixelColor.g += transmittance * transmitColor.g;
					}
				}
			}
		}
		else
		{
			pixelColor.setColor(0,0.6,1.0);
		}
		return pixelColor;
	}
};

#endif