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
		
		void color_t::setr(double k)
	 	{
	   		r = k;
	 	}
		void color_t::setg(double k)
	 	{
	   		g = k;
	 	}
		void color_t::setb(double k)
	 	{
	   		b = k;
	 	}
	 	double color_t::getr() const
		{
			return r;
		}
	 	double color_t::getg() const
		{
			return g;
		}
	 	double color_t::getb() const
		{
			return b;
		}
};