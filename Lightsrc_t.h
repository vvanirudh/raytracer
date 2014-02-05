#ifndef LIGHTSRC_T
#define LIGHTSRC_T

#include "Color_t.h"
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

	Point_t getPos() const
	{
		return p;
	}

	Color_t getColor() const
	{
		return c;
	}
	//Destructor
	//~Lightsrc_t();

	
};
#endif