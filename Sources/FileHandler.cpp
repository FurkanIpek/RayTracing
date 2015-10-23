#include "FileHandler.h"

using std::string;
using std::istringstream;

void FileHandler::ReadFile()
{
	std::fstream reader;

	reader.open(file_name, std::ios::in);

	if ( reader.is_open() )
	{
		// getline 10 times and set the values
		string line, color_str;
		getline(reader, line);
		istringstream stream(line);

		stream >> width >> height;
		
		getline(reader, line);
		stream.str(line);
		stream >> Vmin  >> Vmax;

		getline(reader, line);
		stream.str(line);
		stream >> ray_reflx;

		getline(reader, line);
		stream.str(line);
		stream >> max_ray_reflx;

		getline(reader, line);
		stream.str(line);
		stream >> cx >> cy >> cz;

		/* TODO  Get material parameters */
		getline(reader, line);
		stream.str(line);

		getline(reader, line);
		stream.str(line);
		stream >> tx1 >> ty1 >> tz1 >> tx2 >> ty2 >> tz2 >> tx3 >> ty3 >> tz3 >> ta >> color_str;
		tri_c = Color::DetectColor(color_str, ta);

		getline(reader, line);
		stream.str(line);
		stream >> sx >> sy >> sz >> sa >> sr >> color_str;
		sphere_c = Color::DetectColor(color_str, sa);
		Sphere* sphere = new Sphere(Vector(sx, sy, sz), sr, sphere_c);
		spheres.push_back(sphere);

		getline(reader, line);
		stream.str(line);
		stream >> sx >> sy >> sz >> sa >> sr >> color_str;
		sphere_c = Color::DetectColor(color_str, sa);
		Sphere* sphere2 = new Sphere(Vector(sx, sy, sz), sr, sphere_c);
		spheres.push_back(sphere2);

		getline(reader, line);
		stream.str(line);
		stream >> lx >> ly >> lz >> la >> color_str;
		light_c = Color::DetectColor(color_str, la);

		getline(reader, line);
		stream.str(line);
		stream >> ambient;

		getline(reader, line);
		stream.str(line);
		stream >> color_str;
		background = Color::DetectColor(color_str, 0);
	}
}

FileHandler::~FileHandler()
{
	/*for ( int i = 0; i < spheres.size(); i++ )
		delete spheres.at(i);*/
}