#ifndef COLOR_T_H_
#define COLOR_T_H_

class color_t
{
	public:
		double r, g, b;//red, blue and green components respectively
		//Default Constructor
		color_t(double a, double b, double c)
		{
			r = a;//red
			g = b;//green
			b = c;//blue
		}

		//Default Destructor
		//~color_t();

		//sets RGB values
		void setcolor(double a,double b,double c)
		{	
			r = a;//red
			g = b;//green
			b = c;//blue
		}

		//Copy Constructor
		color_t(color_t& k)
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