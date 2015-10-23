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

#include "../Resources/tiffio.h"

#include <math.h>
#include <vector>

using std::vector;

class ImageRender {

private:

	unsigned char* image;
	TIFF* tif;

	FileHandler fh; // holds all values read from file
	Camera* camera;
	Light* light;
	vector<Sphere*> spheres;
	vector<Triangle*> triangles;
	vector<Plane*> planes;

	void SetTiffHeaders();
	void WriteImageToTiff();
	Ray ComputeRay(double, double);
	void FindIntersections(Ray&, vector<Object*>&);
	Object* FindNearestObj(Ray&, vector<Object*>&);
	void RayTrace(int, int, Ray&, Object*);
	void SetBlack(int, int);
	Color GetColor(Ray&, Object*, int&);

public:
	ImageRender(FileHandler& fh);
	~ImageRender();

	void Render();
};

#endif