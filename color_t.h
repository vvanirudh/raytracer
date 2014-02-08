#ifndef COLOR_T_H_
#define COLOR_T_H_

class Color_t
{
	public:
		double r, g, b;//red, blue and green components respectively
		//Default Constructor
		Color_t(double a, double bl, double c)
		{
			r = a;//red
			g = bl;//green
			b = c;//blue
		}

		Color_t()
		{

		}

		//Default Destructor
		//~Color_t();

		//sets RGB values
		void setColor(double a,double bl,double c)
		{	
			r = a;//red
			g = bl;//green
			b = c;//blue
		}

		void setColor(Color_t c)
		{
			r = c.r;
			g = c.g;
			b = c.b;	
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

		Color_t& operator=(const Color_t& v)
		{
		r = v.r;
		g = v.g;
		b = v.b;
		return *this;
		}
};

#endif
