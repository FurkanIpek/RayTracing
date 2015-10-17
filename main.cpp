#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Object.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vector.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <time.h>

int main(int argc, char* argv [])
{
	Vector org(0,0,0), dir(0,0,1);
	Ray ray(org,dir);
	Color color(5.0, 5.0, 5.0, 5.0);
	Sphere sphere(org, 2, color);

	std::cout << ray.getDirection().getX() ;

	system("pause");
	return 0;
}