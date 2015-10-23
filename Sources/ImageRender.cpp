#include "ImageRender.h"

#include <exception>
#ifdef _DEBUG
#include <iostream>
#endif

#define EPSILON 0.000001

ImageRender::ImageRender(FileHandler& fh) : fh(fh)
{
	Vector X(1, 0, 0);
	Vector Y(0, 1, 0);
	Vector Z(0, 0, 1);

	Vector cam_pos(fh.cx, fh.cy, fh.cz);
	Vector cam_dir = cam_pos.Negative().Normalize();
	Vector cam_right = X.CrossProduct(cam_dir).Normalize();
	Vector cam_down = cam_right.CrossProduct(cam_dir);

	camera = new Camera(cam_pos, cam_dir, cam_right, cam_down);

	Vector light_pos(fh.lx, fh.ly, fh.lz);
	light = new Light(light_pos, fh.light_c);

	spheres = fh.spheres;
	
	Plane* floor = new Plane(Y, -1, Color::DetectColor("white", 0));
	//Plane* zz = new Plane(Z, -fh.Vmax, Color::DetectColor("black", 0));
	//Plane* right = new Plane(X.Negative(), -1, Color::DetectColor("gray", 0));
	Plane* back = new Plane(Y.Negative(), -fh.Vmax, Color::DetectColor("wall", 0));
	planes.push_back(floor);
	planes.push_back(back);
	//planes.push_back(zz);
	//planes.push_back(right);

	Triangle* triangle = new Triangle(Vector(fh.tx1, fh.ty1, fh.tz1), Vector(fh.tx2, fh.ty2, fh.tz2), Vector(fh.tx3, fh.ty3, fh.tz3), fh.tri_c);
	triangles.push_back(triangle);

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
	TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, 1);
}

void ImageRender::WriteImageToTiff()
{
	if(TIFFWriteEncodedStrip(tif, 0, image, fh.width * fh.height * 3) == 0)
		throw new std::exception("Couldn't write :( \n");
}

void ImageRender::Render()
{
	SetTiffHeaders();

	int aadepth = 1;
	double xamnt, yamnt;

	double aspectratio = (double)fh.width/(double)fh.height;
	Color color = Color::DetectColor("purple", 0);
	std::vector<Object*> intersections;
	
	for ( int x = 0; x < fh.height; x++ )
	{
		for ( int y = 0; y < fh.width*3; y+=3 ) // rgb
		{
			xamnt = ((x+0.5)/fh.width)*aspectratio - (((fh.width-fh.height)/(double)fh.height)/2);
			yamnt = ((fh.height - y/3) + 0.5)/fh.height;

			Ray ray = ComputeRay(xamnt, yamnt);
			
			FindIntersections(ray, intersections);

			Object* nearest = FindNearestObj(ray, intersections);

			RayTrace(x, y, ray, nearest);
			
			intersections.clear();
		}
	}
	
	WriteImageToTiff();
}

Ray ImageRender::ComputeRay(double xamnt, double yamnt)
{
	static Vector cam_org = camera->getCameraPosition();

	Vector cam_dir = camera->getCameraDirection().VectorAdd(camera->getCameraRight()
				.VectorMult(xamnt - 0.5).VectorAdd(camera->getCameraDown().VectorMult(yamnt - 0.5))).Normalize();

	return Ray(cam_org, cam_dir);
}

void ImageRender::FindIntersections(Ray& ray, std::vector<Object*>& intersections)
{
	for ( int i = 0; i < planes.size(); i++ )
		if( planes.at(i)->findIntersection(ray) > EPSILON )
			intersections.push_back(planes.at(i));

	for ( int i = 0; i < triangles.size(); i++ )
		if( triangles.at(i)->findIntersection(ray) > EPSILON )
			intersections.push_back(triangles.at(i));

	for ( int i = 0; i < spheres.size(); i++ )
		if( spheres.at(i)->findIntersection(ray) > EPSILON )
			intersections.push_back(spheres.at(i));
}

Object* ImageRender::FindNearestObj(Ray& ray, std::vector<Object*>& intersections)
{
	Object* nearest = nullptr;
	double cur_max = 0;

	for ( int i = 0; i < intersections.size(); i++ )
		if ( intersections.at(i)->findIntersection(ray) > 0 && intersections.at(i)->findIntersection(ray) > cur_max )
		{
			cur_max = intersections.at(i)->findIntersection(ray);
			nearest = intersections.at(i);
		}

	for ( int i = 0; i < intersections.size(); i++ )
		if ( intersections.at(i)->findIntersection(ray) > 0 && intersections.at(i)->findIntersection(ray) < cur_max )
			nearest = intersections.at(i);

	return nearest;
}

void ImageRender::RayTrace(int x, int y, Ray& ray, Object* nearest)
{
	Color color;
	int max_reflection = fh.max_ray_reflx;

	if ( nearest != nullptr )
		color = GetColor(ray, nearest, max_reflection);
	else
		color = Color::DetectColor("black", 128).colorAdd(light->getColor().colorScalar(fh.ambient).clip());
	
	image[(x*fh.width*3)+y] = color.getRed();
	image[(x*fh.width*3)+y+1] = color.getGreen();
	image[(x*fh.width*3)+y+2] = color.getBlue();
}

Color ImageRender::GetColor(Ray& ray, Object* nearest, int& max_reflection)
{
	Color color = nearest->getColor().colorScalar(fh.ambient);
	Vector intr_pos = ray.getOrigin().VectorAdd(ray.getDirection().VectorMult(nearest->findIntersection(ray))),
		intr_ray_dir = ray.getDirection(),
		normal = nearest->getNormalAtPos(intr_pos);
	
	double dot1 = normal.DotProduct(intr_ray_dir.Negative());
	Vector scalar1 = normal.VectorMult(dot1);
	Vector add1 = scalar1.VectorAdd(intr_ray_dir);
	Vector scalar2 = add1.VectorMult(2);
	Vector add2 = intr_ray_dir.Negative().VectorAdd(scalar2);
	Vector reflection_direction = add2.Normalize();

	Ray reflection_ray(intr_pos, reflection_direction);
	
	std::vector<Object*> refl_intersections;

	FindIntersections(reflection_ray, refl_intersections);

	Object* reflectedObj = FindNearestObj(reflection_ray, refl_intersections);

	if ( reflectedObj != nullptr && max_reflection != 0 )
	{
		Color to_add = GetColor(reflection_ray, reflectedObj, --max_reflection);
		color = color.colorAdd(to_add.colorScalar(nearest->getColor().getAlpha()));
	}

	Vector light_dir = light->getPosition().VectorAdd(intr_pos.Negative()).Normalize();

	float cos_angle = normal.DotProduct(light_dir);

	if ( cos_angle > 0 )
	{
		bool shadowed = false;

		Vector distance_to_light = light->getPosition().VectorAdd(intr_pos.Negative()).Normalize();
		float distance_to_light_magnitude = distance_to_light.Magnitude();

		Ray shadow_ray (intr_pos, distance_to_light);
			
		std::vector<Object*> secondary_intersections;
			
		FindIntersections(shadow_ray, secondary_intersections);
			
		for (int c = 0; c < secondary_intersections.size(); c++) {
			if (secondary_intersections.at(c)->findIntersection(shadow_ray) > EPSILON) {
				if (secondary_intersections.at(c)->findIntersection(shadow_ray) <= distance_to_light_magnitude) {
					shadowed = true;
				}
			}
			break;
		}

		if (shadowed == false)
		{
			color = color.colorAdd(nearest->getColor().colorMultiply(light->getColor().colorScalar(cos_angle)));
				
			double dot1 = normal.DotProduct(intr_ray_dir.Negative());
			Vector scalar1 = normal.VectorMult(dot1);
			Vector add1 = scalar1.VectorAdd(intr_ray_dir);
			Vector scalar2 = add1.VectorMult(2);
			Vector add2 = intr_ray_dir.Negative().VectorAdd(scalar2);
			Vector reflection_direction = add2.Normalize();
					
			double specular = reflection_direction.DotProduct(light_dir);
			if (specular > 0) 
			{
				specular = pow(specular, 10);
				color = color.colorAdd(light->getColor().colorScalar(specular*nearest->getColor().getAlpha()));
			}
				
		}

	}
	
	return color.clip();
}

ImageRender::~ImageRender()
{
	TIFFClose(tif);
	delete camera, light;

	for ( int i = 0; i < planes.size(); i++ )
		delete planes.at(i);

	for ( int i = 0; i < triangles.size(); i++ )
		delete triangles.at(i);

	for ( int i = 0; i < spheres.size(); i++ )
		delete spheres.at(i);
}