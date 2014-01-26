#ifndef LIGHTSRC_T
#define LIGHTSRC_T
class Lightsrc_t
{
public:
	Point_t p;//Position of Light Source
	color_t c;//Color of the Light
	//Default Constructor
	Lightsrc_t()
	{

	}

	Lightsrc_t(Point_t a, color_t b)
	{
		p = a;
		c = b;
	}

	Point_t getPos() const
	{
		return p;
	}

	color_t getcolor() const
	{
		return c;
	}
	//Destructor
	//~Lightsrc_t();

	
};
#endif