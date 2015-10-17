#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "Color.h"

#include <fstream>
#include <sstream>
#include <string>

class FileHandler {

private:
	std::string file_name;
	int width, height; // image width & height
	double Vmin, Vmax; // z coor of the front & the end of scene to be rendered
	int ray_reflx, max_ray_reflx; // ray reflection
	double cx, cy, cz; // camera parameters
	// TODO material parameters
	double tx, ty, tz;
	double sx, sy, sz;
	double lx, ly, lz;
	double ambient;
	Color color;

public:
	FileHandler(std::string fn) : file_name(fn) { ReadFile(); }

	void ReadFile();
};

#endif