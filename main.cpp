#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Camera_t.h"
#include "Lightsrc_t.h"
#include "Object_t.h"
#include "Phong_t.h"
#include "Point_t.h"
#include "Scene_t.h"
#include "Sphere_t.h"
#include "Triangle_t.h"
#include "Vector_t.h"
#include "color_t.h"
#include "ray_t.h"

using namespace std;

int HEIGHT =  800;
int  WIDTH =  800;
double NEARPLANE = 1;
double SCALEFACTOR = 0.0075;

int DEPTH;

Color_t ** outputColor;


void init()
{
	glClearColor(0,0,0,1.f);
	glClearDepth(1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,HEIGHT,WIDTH,0);
	// glOrtho(0,HEIGHT,WIDTH,0,-1,1);

	outputColor = new Color_t*[HEIGHT];
	for(int i=0;i<HEIGHT;i++)
		outputColor[i] = new Color_t[WIDTH];

	for(int i=0;i<HEIGHT;i++)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			outputColor[i][j].setColor(0,0,0);
		}
	}


	/** CODE TO BE REMOVED AND REPLACED WITH THE FILE INPUT CODE **/

	DEPTH = 0;

	Point_t p1(0.0,0.0,4.0);
	Point_t p2(0.0,0.0,0.0);
	Point_t p3(0.0,1.0,0.0);
	Camera_t camera(p1,p2,p3);
	Scene_t scene(NEARPLANE,SCALEFACTOR);

	Phong_t ps1;
	Point_t p4(0.1,1.0, 0.1);
	Sphere_t s1(p4, 0.6);

	s1.setPhong(&ps1);
	s1.reflectance = 0.01;
	s1.transmittance = 0.85;
	s1.refIndex = 0.95;
	
	Color_t c1(1.0,1.0,1.0);
	Color_t c2(1.0,1.0,1.0);
	s1.setMaterial(c1,c2 , 0.75,0.75,0.2, 20.0);

	scene.add(&s1);

	Point_t p5(0,5,0);
	Color_t c3(0.4,0.3,0.5);
	Lightsrc_t light(p5, c3);

	scene.add(&light);

	camera.render(scene, HEIGHT, WIDTH, outputColor, 0, DEPTH);

}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);

	for(int i=0;i<HEIGHT;i++)
	{
		for(int j=0;j<WIDTH;j++)
		{
			glColor3f(outputColor[i][j].r, outputColor[i][j].g, outputColor[i][j].b);
			glBegin(GL_POINTS);
			glVertex2i(i,j);
			glEnd();
		}
	}

	glFlush();
	glutSwapBuffers();
}


int main(int argc, char*argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(HEIGHT, WIDTH);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Ray Tracer");
	
	init();
	
	glutDisplayFunc(display);
	// glutKeyboardFunc(keyboard);
	glutMainLoop();
}