#ifndef SPHERE_H
#define SPHERE_H

#include "Vector.h"
#include "Object.h"
#include "Ray.h"

class Sphere: public Object {
private:
	Vector center;
	double radius;
	Color color;
public:
	Sphere(Vector, double, Color);

	Color getColor() { return color; }
	
	Vector getNormalAtPos(Vector&);
	double findIntersection(Ray&);
};

#endif