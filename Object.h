#ifndef OBJECT_H
#define OBJECT_H

#include "Vector.h"
#include "Ray.h"
#include "Color.h"

class Object {

public:
	virtual Color getColor() = 0;
	virtual Vector getNormalAtPos(Vector&) = 0;
	virtual double findIntersection(Ray&) = 0;
};

#endif