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

	DEPTH = 2;

	Point_t p1(0.0,0.0,4.0);
	Point_t p2(0.0,0.0,0.0);
	Point_t p3(0.0,1.0,0.0);
	Camera_t camera(p1,p2,p3);
	Scene_t scene(NEARPLANE,SCALEFACTOR);

	/** FIRST SPHERE **/
	Point_t center(0,0,-2);
	double radius = 1.0;
	Phong_t ps;
	Sphere_t s1(center, radius);
	s1.setPhong(&ps);
	s1.reflectance = 0.0;
	s1.transmittance = 0.0;
	s1.refIndex = 0.95;
	Color_t c11(0.0,1.0,1.0);
	Color_t c12(0.0,1.0,1.0);
	s1.setMaterial(c11, c12, 0.075,0.75,1.0, 40.0);

	scene.add(&s1);

	/** SECOND SPHERE **/
	Point_t center2(0,1.0,0);
	double radius2 = 0.6;
	Phong_t ps2;
	Sphere_t s2(center2, radius2);
	s2.setPhong(&ps2);
	s2.reflectance = 0.0;
	s2.transmittance = 1.0;
	s2.refIndex = 0.95;
	Color_t c21(0.0,1.0,0.0);
	Color_t c22(0.0,1.0,0.0);
	s2.setMaterial(c21, c22, 0.075,0.75,1.0, 40.0);

	scene.add(&s2);

	/** FIRST TRIANGLE **/
	Point_t pt1(0,0,1);
	Point_t pt2(-0.5,0,1);
	Point_t pt3(-1.0,0,1);
	Phong_t pst1;
	Triangle_t t1(pt1,pt2,pt3);
	t1.setPhong(&pst1);
	t1.reflectance = 0.65;
	t1.transmittance = 0.0;
	t1.refIndex = 0.95;
	Color_t ct1(1.0,0.0,0.0);
	Color_t ct2(1.0,0.0,0.0);
	t1.setMaterial(ct1, ct2, 0.075,0.75,1.0, 40.0);

	// scene.add(&t1);

	/** Light **/
	Point_t pl1(-2000.0,0,0);
	Color_t cl1(1.0,1.0,1.0);
	Lightsrc_t light1(pl1, cl1);
	// scene.add(&light1);

	Point_t pl2(0,-1000,0);
	Color_t cl2(1.0,1.0,1.0);
	Lightsrc_t light2(pl2, cl2);
	// scene.add(&light2);

	Point_t pl3(0.0,0,2000);
	Color_t cl3(1.0,1.0,1.0);
	Lightsrc_t light3(pl3, cl3);
	scene.add(&light3);


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