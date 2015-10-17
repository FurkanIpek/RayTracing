#include "Plane.h"

Plane::Plane(Vector v, double d, Color c)
{
	normal = v;
	distance = d;
	color = c;
}

Vector Plane::getNormalAtPos(Vector& vect)
{
	return normal;
}

double Plane::findIntersection(Ray& ray)
{
	double a = ray.getDirection().DotProduct(normal);

	if ( a == 0 ) return 0; // ray is parallel to the plane

	double b = normal.DotProduct(ray.getOrigin().VectorAdd(normal.VectorMult(distance).Negative()));

	return -1*b/a;
}