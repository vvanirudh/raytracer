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
#include <fstream>
#include <cstdlib>
#include "Cylinder_t.h"

using namespace std;

int HEIGHT =  800;
int  WIDTH =  800;
double NEARPLANE = 1;
double SCALEFACTOR = 0.0075;

int DEPTH;

Color_t ** outputColor;

bool recording=true;
unsigned char *pRGB;


void capture_frame()
{
  //global pointer float *pRGB
  pRGB = new unsigned char [3 * (WIDTH+1) * (HEIGHT + 1) ];


  // set the framebuffer to read
  //default for double buffered
  glReadBuffer(GL_BACK);

  glPixelStoref(GL_PACK_ALIGNMENT,1);//for word allignment
  
  glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pRGB);
  char filename[200];
  sprintf(filename,"images/frame.ppm");
  std::ofstream out(filename, std::ios::out);
  out<<"P6"<<std::endl;
  out<<WIDTH<<" "<<HEIGHT<<" 255"<<std::endl;
  out.write(reinterpret_cast<char const *>(pRGB), (3 * (WIDTH+1) * (HEIGHT + 1)) * sizeof(int));
  out.close();

  //function to store pRGB in a file named count
  delete pRGB;
}

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

	Scene_t scene(NEARPLANE, SCALEFACTOR);
	Camera_t *camera;
	string f;
    // cout<<"Enter the scene file name to be loaded\n";
    // cin>>f;
    ifstream input_file;
    // input_file.open(f.c_str());
    input_file.open("sample_file");
    int i = 0;
    vector<Sphere_t> spheres;
    std::vector<Triangle_t> triangles;
    vector<Lightsrc_t> lights;
    std::vector<Cylinder_t> cylinders;
    while(input_file.good())
    {
        string str, par;
        getline(input_file,str);
        int psn;
        vector<string> parse;
        while((psn = str.find(" ")) != string::npos)
        {
            par = str.substr(0,psn);
            parse.push_back(par);
            str = str.substr(psn+1);
            //std::cout<<"2";
        }
        if(i == 0)
        {
            WIDTH = atoi(parse[0].c_str());
            HEIGHT = atoi(parse[1].c_str());
            DEPTH  = atoi(parse[2].c_str());
        }
        else if(i == 1)
        {
            Point_t p(atof(parse[0].c_str()), atof(parse[1].c_str()), atof(parse[2].c_str()));
            // camera.pos = p;
            Point_t p1(atof(parse[3].c_str()),atof(parse[4].c_str()),atof(parse[5].c_str()));
            // camera.lookAt = p1;
            Point_t p2(atof(parse[6].c_str()),atof(parse[7].c_str()),atof(parse[8].c_str()));
            // camera.up = p2;
            camera = new Camera_t(p,p1,p2);
        }
        else
        {
            if(parse[0] == "S")
            {
                // setMaterial(Color_t diff, Color_t spec, double ambCoeff, double diffCoeff, double specCoeff, double exponent)
                Point_t a(atof(parse[1].c_str()), atof(parse[2].c_str()), atof(parse[3].c_str()));
                Sphere_t S1(a,atof(parse[4].c_str()));
                Color_t diff(atof(parse[5].c_str()), atof(parse[6].c_str()), atof(parse[7].c_str()));
                Color_t spec(atof(parse[8].c_str()), atof(parse[9].c_str()), atof(parse[10].c_str()));
                Phong_t ps1;
                S1.setPhong(&ps1);
                S1.setMaterial(diff,spec,atof(parse[11].c_str()),atof(parse[12].c_str()),atof(parse[13].c_str()),atof(parse[14].c_str()));
                S1.reflectance = atof(parse[15].c_str());
				S1.transmittance = atof(parse[16].c_str());
				S1.refIndex = atof(parse[17].c_str());
                // scene.add(&S1);
                spheres.push_back(S1);
            }
            else if(parse[0] == "T")
            {
                Point_t a(atof(parse[1].c_str()), atof(parse[2].c_str()), atof(parse[3].c_str()));
                Point_t b(atof(parse[3].c_str()), atof(parse[5].c_str()), atof(parse[6].c_str()));
                Point_t c(atof(parse[7].c_str()), atof(parse[8].c_str()), atof(parse[9].c_str()));
                Triangle_t T1(a,b,c);
                Color_t diff(atof(parse[10].c_str()), atof(parse[11].c_str()), atof(parse[12].c_str()));
                Color_t spec(atof(parse[13].c_str()), atof(parse[14].c_str()), atof(parse[15].c_str()));
                Phong_t pT1;
                T1.setPhong(&pT1);
                T1.setMaterial(diff,spec,atof(parse[16].c_str()),atof(parse[17].c_str()),atof(parse[18].c_str()),atof(parse[19].c_str()));
                T1.reflectance = atof(parse[20].c_str());
				T1.transmittance = atof(parse[21].c_str());
				T1.refIndex = atof(parse[22].c_str());
                // scene.add(&T1);
                triangles.push_back(T1);
            }    
            else if(parse[0] == "L")
            {
                Point_t a(atof(parse[1].c_str()), atof(parse[2].c_str()), atof(parse[3].c_str()));
                Color_t b(atof(parse[4].c_str()), atof(parse[5].c_str()), atof(parse[6].c_str()));
                Lightsrc_t L1(a,b);
                // scene.add(&L1);
                lights.push_back(L1);
            }
            else if(parse[0] == "CL")
            {
            	Point_t a(atof(parse[1].c_str()), atof(parse[2].c_str()), atof(parse[3].c_str()));
            	double r = atof(parse[4].c_str());
            	double h = atof(parse[5].c_str());
            	Vector_t v(atof(parse[6].c_str()), atof(parse[7].c_str()), atof(parse[8].c_str()));
            	Cylinder_t cl1(a,r,h,v);
            	Color_t diff(atof(parse[9].c_str()), atof(parse[10].c_str()), atof(parse[11].c_str()));
                Color_t spec(atof(parse[12].c_str()), atof(parse[13].c_str()), atof(parse[14].c_str()));
                Phong_t pcl1;
                cl1.setPhong(&pcl1);
                cl1.setMaterial(diff,spec,atof(parse[15].c_str()),atof(parse[16].c_str()),atof(parse[17].c_str()),atof(parse[18].c_str()));
                cl1.reflectance = atof(parse[19].c_str());
				cl1.transmittance = atof(parse[20].c_str());
				cl1.refIndex = atof(parse[21].c_str());
				cylinders.push_back(cl1);
            }
            else if(parse[0] == "#")
            {

            }
        }
       i++;
   }
   input_file.close();

   for (std::vector<Sphere_t>::iterator i = spheres.begin(); i != spheres.end(); ++i)
   {
   		scene.add(&(*i));
   		cout<<"Sphere added\n";
   }

   for (std::vector<Triangle_t>::iterator i = triangles.begin(); i != triangles.end(); ++i)
   {
   		cout<<"Triangle added\n";
   		scene.add(&(*i));
   		
   }

   for (std::vector<Lightsrc_t>::iterator i = lights.begin(); i != lights.end(); ++i)
   {
   		cout<<"Light added\n";
   		scene.add(&(*i));
   }

   for (std::vector<Cylinder_t>::iterator i = cylinders.begin(); i != cylinders.end(); ++i)
   {
   		cout<<"Cylinder added\n";
   		scene.add(&(*i));
   }

	/** CODE TO BE REMOVED AND REPLACED WITH THE FILE INPUT CODE **/

	// DEPTH = 2;

	// Point_t p1(0.0,0.0,4.0);
	// Point_t p2(0.0,0.0,0.0);
	// Point_t p3(0.0,1.0,0.0);
	// Camera_t camera(p1,p2,p3);
	// Scene_t scene(NEARPLANE,SCALEFACTOR);

	// /** FIRST SPHERE **/
	// Point_t center(0,0,-2);
	// double radius = 1.0;
	// Phong_t ps;
	// Sphere_t s1(center, radius);
	// s1.setPhong(&ps);
	// s1.reflectance = 0.0;
	// s1.transmittance = 0.0;
	// s1.refIndex = 0.95;
	// Color_t c11(0.0,1.0,1.0);
	// Color_t c12(0.0,1.0,1.0);
	// s1.setMaterial(c11, c12, 0.075,0.75,1.0, 40.0);

	// // scene.add(&s1);

	// /** SECOND SPHERE **/
	// Point_t center2(0,1.0,0);
	// double radius2 = 0.6;
	// Phong_t ps2;
	// Sphere_t s2(center2, radius2);
	// s2.setPhong(&ps2);
	// s2.reflectance = 0.0;
	// s2.transmittance = 1.0;
	// s2.refIndex = 0.95;
	// Color_t c21(0.0,1.0,0.0);
	// Color_t c22(0.0,1.0,0.0);
	// s2.setMaterial(c21, c22, 0.075,0.75,1.0, 40.0);

	// // scene.add(&s2);

	// /** FIRST TRIANGLE **/
	// Point_t pt1(0,0,0);
	// Point_t pt2(-2,0,0);
	// Point_t pt3(0,2,0);
	// Phong_t pst1;
	// Triangle_t t1(pt1,pt2,pt3);
	// t1.setPhong(&pst1);
	// t1.reflectance = 0.0;
	// t1.transmittance = 0.0;
	// t1.refIndex = 0.95;
	// Color_t ct1(1.0,0.0,0.0);
	// Color_t ct2(1.0,0.0,0.0);
	// t1.setMaterial(ct1, ct2, 0.075,0.75,1.0, 40.0);

	// scene.add(&t1);

	// /** Light **/
	// Point_t pl1(2000.0,0,0);
	// Color_t cl1(1.0,1.0,1.0);
	// Lightsrc_t light1(pl1, cl1);
	// scene.add(&light1);

	// Point_t pl2(0,1,200);
	// Color_t cl2(1.0,1.0,1.0);
	// Lightsrc_t light2(pl2, cl2);
	// scene.add(&light2);

	// Point_t pl3(0.0,0,200);
	// Color_t cl3(1.0,1.0,1.0);
	// Lightsrc_t light3(pl3, cl3);
	// scene.add(&light3);


	camera->render(scene, HEIGHT, WIDTH, outputColor, 0, DEPTH);

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
	if (recording)
		capture_frame();
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