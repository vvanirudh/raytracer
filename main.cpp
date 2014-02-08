#include <iostream>
#include <GL/glut.h>

using namespace std;

#define HEIGHT 500
#define WIDTH 500

Color_t outputColor[HEIGHT][WIDTH];


void init(char * file)
{
	glClearColor(0,0,0,1.f);
	glClearDepth(1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,HEIGHT,WIDTH,0);

	
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