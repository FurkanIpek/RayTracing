#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "Vector.h"
#include "Color.h"

class Triangle: public Object {

private:
	Vector A, B, C;
	Color color;
	Vector edge_1, edge_2;

public:
	Triangle();
	Triangle(Vector a, Vector b, Vector c, Color color);

	Color getColor() { return color; }

	Vector getNormalAtPos(Vector&);
	double findIntersection(Ray&);
};

#endif