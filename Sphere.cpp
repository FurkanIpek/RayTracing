#include "Sphere.h"
#include <math.h>

Sphere::Sphere(Vector v, double r, Color c)
{
	center = v;
	radius = r;
	color = c;
}

Vector Sphere::getNormalAtPos(Vector& vec)
{
	return vec.VectorAdd(center.Negative()).Normalize();;
}

double Sphere::findIntersection(Ray& ray)
{
	double b = 2*((ray.getOrigin().getX() - center.getX())*ray.getDirection().getX()
		+ (ray.getOrigin().getY() - center.getY())*ray.getDirection().getY()
		+ (ray.getOrigin().getZ() - center.getZ())*ray.getDirection().getZ());

	double c = pow(ray.getOrigin().getX() - center.getX(), 2)
		+ pow(ray.getOrigin().getY() - center.getY(), 2)
		+ pow(ray.getOrigin().getZ() - center.getZ(), 2)
		+ (radius*radius);

	double discriminant = b*b - 4*c;

	if ( discriminant > 0 )
	{
		double root_1 = ((-1*b - sqrt(discriminant))/2) - 0.000001;
		double root_2 = ((sqrt(discriminant) - b)/2) - 0.000001;

		return root_1 > 0 ? root_1 : root_2;
	}

	return -1;
}