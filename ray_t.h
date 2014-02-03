#ifndef RAY_T
#define RAY_T
class Ray_t
{
	public:
		Point_t org; // the starting point of the ray

		Vector_t dir; // this gives the direction of the ray

		//Default Constructor
		Ray_t()
		{

		}

		Ray_t(Point_t a, Vector_t b)
		{
			org = a;
			dir = b;
		}
		void setOrg(Point_t a)
		{
			org = a;
		}
		void setDirection(Vector_t a)
		{
			dir = a;
		}
};
#endif