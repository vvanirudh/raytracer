#ifndef LIGHTSRC_T
#define LIGHTSRC_T

#include "color_t.h"
#include "Point_t.h"

class Lightsrc_t
{
public:
	Point_t p;//Position of Light Source
	Color_t c;//Color of the Light
	//Default Constructor
	Lightsrc_t()
	{

	}

	Lightsrc_t(Point_t a, Color_t b)
	{
		p = a;
		c = b;
	}

	Lightsrc_t(const Lightsrc_t& l)
	{
		p = l.p;
		c = l.c;
	}

	Point_t getPos()
	{
		return p;
	}

	Color_t getColor()
	{
		return c;
	}
	//Destructor
	//~Lightsrc_t();

	
};
#endif