#ifndef IMAGE_RENDER_H
#define IMAGE_RENDER_H

#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Object.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vector.h"
#include "Triangle.h"
#include "FileHandler.h"
#include "ImageRender.h"

#include <math.h>
#include <string>
#include <time.h>

class ImageRender {

private:
	double* image;

	FileHandler fh; // holds all values read from file
	Camera* camera;
	Light* light;
	Sphere* sphere;
	Triangle* triangle;
	Plane* plane;

public:
	ImageRender(FileHandler& fh);
	~ImageRender();

	void Render();
};

#endif