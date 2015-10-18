#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include "Vector.h"
#include "Color.h"
#include "Ray.h"

class Plane: public Object {

private:
	Vector normal;
	double distance;
	Color color;

public:
	Plane() : distance(0.0) {}
	Plane(Vector, double, Color);

	Color getColor() { return color; }

	Vector getNormalAtPos(Vector&);
	double findIntersection(Ray&);
};

#endif