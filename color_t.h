#ifndef COLOR_T_H_
#define COLOR_T_H_

class Color_t
{
	public:
		double r, g, b;//red, blue and green components respectively
		//Default Constructor
		Color_t(double a, double b, double c)
		{
			r = a;//red
			g = b;//green
			b = c;//blue
		}

		//Default Destructor
		//~Color_t();

		//sets RGB values
		void setcolor(double a,double b,double c)
		{	
			r = a;//red
			g = b;//green
			b = c;//blue
		}

		//Copy Constructor
		Color_t(Color_t& k)
		{
			r = k.r;//red
			g = k.g;//green
			b = k.b;//blue
		}
		
		void setr(double k)
	 	{
	   		r = k;
	 	}
		void setg(double k)
	 	{
	   		g = k;
	 	}
		void setb(double k)
	 	{
	   		b = k;
	 	}
	 	double getr() const
		{
			return r;
		}
	 	double getg() const
		{
			return g;
		}
	 	double getb() const
		{
			return b;
		}
};

#endif