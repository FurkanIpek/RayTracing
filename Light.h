#ifndef LIGHT_H
#define LIGHT_H

#include "Vector.h"
#include "Color.h"

class Light {
private:
	Vector position;
	Color color;

public:
	Light(Vector p, Color c) : position(p), color(c) {}

	Vector getPosition() { return position; }
	Color getColor() { return color; }
};

#endif