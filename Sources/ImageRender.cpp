#include "ImageRender.h"

#define cimg_use_tiff
#include "../Resources/CImg.h"

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

	image = new double(fh.height*fh.width*3);
}

void ImageRender::Render()
{
	cimg_library::CImg<double> out_img(fh.width, fh.height, 1, 0, 64);
	
	for ( int i = 0; i < out_img.width(); i++ )
	{
		for ( int j = 0; j < out_img.height(); j++ )
		{
			//out_img.set_linear_atX(50, i, j);
		}
	}

	out_img.save_tiff("KavrukCizgeler.tiff");
}

ImageRender::~ImageRender()
{
	delete camera, light, sphere, triangle, plane;
}