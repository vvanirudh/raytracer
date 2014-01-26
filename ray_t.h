#ifndef RAY_T
#define RAY_T value
class ray_t
{
	public:
		Point_t p; // the starting point of the ray

		Vector_t v; // this gives the direction of the ray

		//Default Constructor
		ray_t()
		{

		}

		ray_t(Point_t a, Vector_t b)
		{
			p = a;
			v = b;
		}

		//Destructor
		~ray_t();

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