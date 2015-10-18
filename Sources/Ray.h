#ifndef RAY_H
#define RAY_H

#include "Vector.h"

class Ray {
private:
	Vector origin, direction;

public:
	Ray(Vector origin, Vector direction) : origin(origin), direction(direction) {}

	Vector getOrigin() { return origin; }
	Vector getDirection() { return direction; }
};

#endif