#include "ImageRender.h"
#include <vector>

#define cimg_use_tiff
#include "../Resources/CImg.h"

using namespace cimg_library;

Vector O (0,0,0);
Vector X (1,0,0);
Vector Y (0,1,0);
Vector Z (0,0,1);

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

	image = new int(fh.height*fh.width*3);
}

void ImageRender::Render()
{
	//CImg<double> out_img(fh.width, fh.height, 1, 0, 64);
	int aadepth = 1;
	int xamnt, yamnt;
	
	for ( int x = 0; x < fh.height; x++ )
	{
		for ( int y = 0; y < fh.width*3; y+=3 ) // rgb
		{
			xamnt = (x + 0.5)/fh.width;
			yamnt = ((fh.height - y) + 0.5)/fh.height;

			Ray ray = ComputeRay(xamnt, yamnt);
			
			FindIntersections(ray);

			ObjType nearest = FindNearestObj();

			if ( nearest == none )
				SetBlack(x, y);
			else
				RayTrace(ray, nearest);
		}
	}
	
	//out_img.save_tiff("KavrukCizgeler.tiff");
}

Ray ImageRender::ComputeRay(int xamnt, int yamnt)
{
	static Vector cam_org = camera->getCameraPosition();

	Vector cam_dir = camera->getCameraDirection().VectorAdd(camera->getCameraRight()
				.VectorMult(xamnt - 0.5).VectorAdd(camera->getCameraDown().VectorMult(yamnt - 0.5))).Normalize();

	return Ray(cam_org, cam_dir);
}

void ImageRender::FindIntersections(Ray& ray)
{
	double pd = plane->findIntersection(ray);
	double td = triangle->findIntersection(ray);
	double sd = sphere->findIntersection(ray);
}

ObjType ImageRender::FindNearestObj()
{
	return none;
}

void ImageRender::SetBlack(int x, int y)
{
	static Color black = Color::DetectColor("black" ,0);
	image[(x*y)] = black.getRed();
	image[(x*y)+1] = black.getGreen();
	image[(x*y)+2] = black.getBlue();
}

void ImageRender::RayTrace(Ray ray, ObjType nearest)
{
	Color color = GetColor(ray, nearest);
	Vector intersect_pos, intersect_ray_dir;

	switch(nearest)
	{
	case plane_o:
		
		break;

	case triangle_o:

		break;

	case sphere_o:

		break;
	}

	CheckReflection();
}

Color ImageRender::GetColor(Ray ray, ObjType obj)
{
	switch(obj)
	{
	case plane_o:
		
		break;

	case triangle_o:

		break;

	case sphere_o:

		break;
	}

	return Color::DetectColor("black", 0);
}

void ImageRender::CheckReflection()
{

}

ImageRender::~ImageRender()
{
	delete camera, light, sphere, triangle, plane;
}