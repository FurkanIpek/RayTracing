#include "ImageRender.h"

#include <exception>

#define EPSILON 0.000001

Vector O (0,0,0);
Vector X (1,0,0);
Vector Y (0,1,0);
Vector Z (0,0,1);
// intersection values
double pd;
double td;
double sd;

ImageRender::ImageRender(FileHandler& fh) : fh(fh)
{
	Vector cam_pos(fh.cx, fh.cy, fh.cz);
	Vector cam_dir = cam_pos.Negative().Normalize();
	Vector cam_right = Y.CrossProduct(cam_dir).Normalize();
	Vector cam_down = cam_right.CrossProduct(cam_dir);

	camera = new Camera(cam_pos, cam_dir, cam_right, cam_down);

	Vector light_pos(fh.lx, fh.ly, fh.lz);
	light = new Light(light_pos, fh.light_c);

	sphere = new Sphere(Vector(fh.sx, fh.sy, fh.sz), fh.sr, fh.sphere_c);

	plane = new Plane(Y, -1, Color::DetectColor("floor", 100));

	triangle = new Triangle(Vector(fh.tx1, fh.ty1, fh.tz1), Vector(fh.tx2, fh.ty2, fh.tz2), Vector(fh.tx3, fh.ty3, fh.tz3), fh.tri_c);

	image = new unsigned char [fh.height*fh.width*3];

	tif = TIFFOpen("foo.tif", "w");
}

void ImageRender::SetTiffHeaders()
{
	// TODO ask ftw
	TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, fh.width);
	TIFFSetField(tif, TIFFTAG_IMAGELENGTH, fh.height);
	TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_DEFLATE);
	TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
	TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 3);
	TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
	TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
	TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
	TIFFSetField(tif, TIFFTAG_XRESOLUTION, 150.0);
	TIFFSetField(tif, TIFFTAG_YRESOLUTION, 150.0);
	TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, 0);
}

void ImageRender::WriteImageToTiff()
{
	if(TIFFWriteEncodedStrip(tif, 0, image, fh.width * fh.height * 3) == 0)
	{
		throw new std::exception("Couldn't write :( \n");
	}
}

void ImageRender::Render()
{
	SetTiffHeaders();

	int aadepth = 1;
	int xamnt, yamnt;

	std::vector<double> intersections;
	
	for ( int x = 0; x < fh.height; x++ )
	{
		for ( int y = 0; y < fh.width*3; y+=3 ) // rgb
		{
			xamnt = (x + 0.5)/fh.width;
			yamnt = ((fh.height - y/3) + 0.5)/fh.height;

			Ray ray = ComputeRay(xamnt, yamnt);
			
			FindIntersections(ray, intersections);

			ObjType nearest = FindNearestObj(intersections);

			RayTrace(x, y, ray, nearest);

			intersections.clear();
		}
	}

	WriteImageToTiff();
}

Ray ImageRender::ComputeRay(int xamnt, int yamnt)
{
	static Vector cam_org = camera->getCameraPosition();

	Vector cam_dir = camera->getCameraDirection().VectorAdd(camera->getCameraRight()
				.VectorMult(xamnt - 0.5).VectorAdd(camera->getCameraDown().VectorMult(yamnt - 0.5))).Normalize();

	return Ray(cam_org, cam_dir);
}

void ImageRender::FindIntersections(Ray& ray, std::vector<double>& intersections)
{
	pd = plane->findIntersection(ray);
	if ( pd > EPSILON ) intersections.push_back(pd);

	td = triangle->findIntersection(ray);
	if ( td > EPSILON ) intersections.push_back(pd);

	sd = sphere->findIntersection(ray);
	if ( sd > EPSILON ) intersections.push_back(pd);
}

ObjType ImageRender::FindNearestObj(std::vector<double>& intersections)
{
	double cur_min = 0;
	// TODO ask the reasoning behind finding minimum positive value
	for ( int i = 0; i < intersections.size(); i++ )
		if ( intersections.at(i) > EPSILON && intersections.at(i) <= cur_min )
			cur_min = intersections.at(i);

	if ( cur_min != EPSILON )
	{
		if ( cur_min == pd )
			return plane_o;
		else if ( cur_min == td )
			return triangle_o;
		else if ( cur_min == pd )
			return plane_o;
	}

	return none;
}

void ImageRender::RayTrace(int x, int y, Ray& ray, ObjType nearest)
{
	Color color;

	switch(nearest)
	{
	case plane_o:
		color = GetColor(ray, nearest, pd);
		break;

	case triangle_o:
		color = GetColor(ray, nearest, td);
		break;

	case sphere_o:
		color = GetColor(ray, nearest, sd);
		break;

	default: // none of the objects were hit
		color = Color::DetectColor("black", 0);
	}

	image[(x*y)] = color.getRed();
	image[(x*y)+1] = color.getGreen();
	image[(x*y)+2] = color.getBlue();

	CheckReflection();
}

Color ImageRender::GetColor(Ray& ray, ObjType obj, double mult)
{
	Color color;
	Vector intr_pos = ray.getOrigin().VectorAdd(ray.getDirection().VectorMult(mult)),
			intr_ray_dir = ray.getDirection();

	switch(obj)
	{
	case plane_o:
		color = plane->getColor().colorScalar(fh.ambient);
		break;

	case triangle_o:
		color = triangle->getColor().colorScalar(fh.ambient);
		break;

	case sphere_o:
		color = sphere->getColor().colorScalar(fh.ambient);
		break;
	}

	return color.clip();
}

void ImageRender::CheckReflection()
{

}

ImageRender::~ImageRender()
{
	TIFFClose(tif);
	delete camera, light, sphere, triangle, plane;
}