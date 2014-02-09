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
#include <iostream>

using namespace std;

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

	void render(Scene_t s, int h, int w, Color_t** finalColor, int depth, int DEPTH)
	{
		Ray_t cameraRay(pos);

		for(int x = -h/2; x<h/2; x++)
		{
			for(int y = -w/2;y<w/2; y++)
			{
				finalColor[x + (h/2)][y + (w/2)].setColor(0,0,0);
				s.releaseRay(&cameraRay,x,y);
				// finalColor[x][y].setColor(computeColor(cameraRay, depth, s));
				Color_t c;
				c = computeColor(cameraRay, depth, &s, DEPTH);
				// cout<<c;
				finalColor[x+(h/2)][y+(w/2)].setColor(c);
				// cout<<c.r<<" "<<c.g<<" "<<c.b<<"\n";
			}
		}
	}

	Color_t computeColor(Ray_t r, int depth, Scene_t* s, int DEPTH)
	{
		Color_t ambientColor(0,0,0);
		depth++;
		Color_t pixelColor;
		int nObjects = s->Objects.size();
		bool intersectRay = false;
		Object_t * obj;
		Point_t tempInt;
		Point_t finalInt;
		double tempDist = 0.0;
		double finalDist = 1000000.0;
		bool shadow = false;
		double shadowDist;

		for(int i=0;i<nObjects;i++)
		{
			intersectRay = s->Objects[i]->intersect(r, &tempDist, &tempInt);
			if(intersectRay)
			{
				if(tempInt != r.org)
				{
					
					if(abs(tempDist) < finalDist)
					{
						shadow = true;
						finalDist = abs(tempDist);
						finalInt = tempInt;
						obj = (s->Objects[i]);
					}
				}
			}
		}
		vector<Data> dataVec;
		Data data1;
		if(shadow)
		{
			Data data;
			intersectRay = false;
			tempDist = 0.0;
			finalDist = 1000000.0;

			bool inShadow = false;

			// vector<Lightsrc_t*>::iterator lightItr;
			int nLights = s->Lights.size();

			for(int j=0; j<nLights; ++j)
			{
				Ray_t shadowray;
				shadowray.org = (s->Lights[j]->getPos());

				s->releaseShadowRay(&shadowray, &finalInt);
				Object_t * objRef;

				shadowDist = shadowray.org.distanceBetween(finalInt);

				shadowDist = shadowDist - 0.01;

				for(int i=0;i<nObjects;i++)
				{
					intersectRay = s->Objects[i]->intersect(shadowray, &tempDist, &tempInt);

					if(intersectRay)
					{

						if(tempInt!=finalInt)
						{
							if(abs(tempDist)< finalDist)
							{
								finalDist = abs(tempDist);
								objRef = s->Objects[i];
							}

							/*** inShadow code **/
						}
					}
				}

				
				data.lSrc = s->Lights[j];
				data.inRay = shadowray;
				data.normal = obj->getNormal(finalInt);

				Ray_t viewRay(finalInt);

				Vector_t viewVec;
				viewVec = r.org - finalInt;
				viewVec.normalizeVector();
				viewRay.setDirection(viewVec);
				data.viewRay = viewRay;
				data.point = finalInt;

				Ray_t refRay(finalInt);
				Vector_t refDir;
				refDir = 2*((shadowray.dir * data.normal) * (data.normal)) - (shadowray.dir);
				refDir.normalizeVector();
				refRay.setDirection(refDir);
				data.refRay = refRay;
				data1 = data;
				if(finalDist > shadowDist)
					dataVec.push_back(data);
			}


			if(!(dataVec.empty()))
			{
				obj->phong->illuminate(dataVec, ambientColor, obj->diffuseColor, obj->specularColor, obj->diffuseColor);
				// obj->phong->illuminate()
			}
			else
			{
				obj->phong->illuminateAmbient(ambientColor, obj->diffuseColor);
			}

			pixelColor = obj->phong->color;
			// cout<<pixelColor;
			// cout<<pixelColor.r<<" "<<pixelColor.g<<" "<<pixelColor.b<<endl;

			if(depth < DEPTH)
			{
				Color_t refColor;

				if((obj->reflectance) > 0.0)
				{
					Ray_t reflRay(finalInt);
					Vector_t reflDir;
					reflDir = r.dir - 2*(r.dir*data1.normal)*(data1.normal);
					reflDir.normalizeVector();
					reflRay.setDirection(reflDir);

					double reflectance = obj->reflectance;

					// refColor.setColor(computeColor(reflRay, depth, s, DEPTH));
					refColor = computeColor(reflRay, depth, s, DEPTH);
					// cout<<refColor;
					pixelColor.r += reflectance * refColor.r;
					pixelColor.b += reflectance * refColor.b;
					pixelColor.g += reflectance * refColor.g;
				}

				if((obj->transmittance) > 0.0)
				{
					Ray_t transmitRay(finalInt);
					Vector_t normal;
					normal = -(data1.normal);
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
						Vector_t transmitDir;
						transmitDir = (n * r.dir) + (n * (-(r.dir) * normal) -  tir) * normal;
						transmitDir.normalizeVector();
						transmitRay.setDirection(transmitDir);
						Color_t transmitColor;
						transmitColor = (computeColor(transmitRay, depth, s, DEPTH));

						cout<<transmitColor;

						pixelColor.r += transmittance * transmitColor.r;
						pixelColor.b += transmittance * transmitColor.b;
						pixelColor.g += transmittance * transmitColor.g;
					}
				}
			}
			// cout<<pixelColor;
		}
		else
		{
			pixelColor.setColor(0,0,0);
		}
		return pixelColor;
	}
};

#endif