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
#include <string>
#include <time.h>

#define EPSILON 0.000001

using std::cout;
using std::cin;
using std::string;

int main(int argc, char* argv [])
{
	string file_name = "image.prop";
	if ( argc < 2 )
		cout << "Default file name: image.prop\n";
	else
		file_name = argv[1];

	string c;
	cin >> c;
	return 0;
}