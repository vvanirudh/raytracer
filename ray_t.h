#ifndef RAY_T
#define RAY_T
class Ray_t
{
	public:
		Point_t p; // the starting point of the ray

		Vector_t v; // this gives the direction of the ray

		//Default Constructor
		Ray_t()
		{

		}

		Ray_t(Point_t a, Vector_t b)
		{
			p = a;
			v = b;
		}

		//Destructor
		//~Ray_t();

		Point_t getp() const
		{
			return p;
		}

		Vector_t getv() const
		{
			return v;
		}
};
#endif