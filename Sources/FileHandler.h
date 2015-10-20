#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "Color.h"

#include <fstream>
#include <sstream>
#include <string>

class FileHandler {

public:
	std::string file_name;
	int width, height; // image width & height
	double Vmin, Vmax; // z coor of the front & the end of scene to be rendered
	int ray_reflx, max_ray_reflx; // ray reflection
	double cx, cy, cz; // camera parameters
	// TODO material parameters
	double tx1, tx2, tx3, ty1, ty2, ty3, tz1, tz2, tz3, ta; // triangle x, y, z & alpha values
	Color tri_c; // triangle color
	double sx, sy, sz, sa, sr; // sphere x, y, z, alpha & radius
	Color sphere_c; // sphere color
	double lx, ly, lz, la; // light source x, y, z, alpha(0)
	Color light_c; // light color
	double ambient;
	Color background;

	FileHandler(std::string fn) : file_name(fn) { ReadFile(); }

private:
	void ReadFile();
};

#endif