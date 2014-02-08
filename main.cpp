#include <iostream>
#include <GL/glut.h>

using namespace std;

int HEIGHT =  500;
int  WIDTH =  500;
double NEARPLANE = 1;
double SCALEFACTOR = 0.0075;

int depth;

Color_t outputColor[HEIGHT][WIDTH];


void init(char * file)
{
	glClearColor(0,0,0,1.f);
	glClearDepth(1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,HEIGHT,WIDTH,0);


	/** CODE TO BE REMOVED AND REPLACED WITH THE FILE INPUT CODE **/

	depth = 0;

	Camera_t camera(Point_t(0.0,0.0,4.0),Point_t(0.0,0.0,0.0),Point_t(0.0,1.0,0.0));
	Scene_t scene(NEARPLANE,SCALEFACTOR);

	Phong_t ps1;
	Sphere_t s1(Point_(0.43, 0.2, 0.9), 0.6);

	s1.setPhong(&ps1);
	s1.reflectance = 0.01;
	s1.transmittance = 0.85;
	s1.refIndex = 0.95;
	
	s1.setMaterial(Color_t(1.0,1.0,1.0), Color_t(1.0,1.0,1.0), 0.075,0.075,0.2, 20.0);

	scene.add(&s1);

	Lightsrc_t light(Point_t(0,5,0), Color_t(0.4,0.3,0.5));

	scene.add(&light);

	camera.render(scene, HEIGHT, WIDTH, outputColor, depth);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);

	for(int i=0;i<HEIGHT;i++)
	{
		for(int j=0;j<WIDTH;j++)
		{
			glColor3f(outputColor[x][y].r, outputColor[x][y].g, outputColor[x][y].b);
			glBegin(GL_POINTS);
			glVertex2i(x,y);
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
	
	init(argv[1]);
	
	glutDisplayFunc(display);
	// glutKeyboardFunc(keyboard);
	glutMainLoop();
}