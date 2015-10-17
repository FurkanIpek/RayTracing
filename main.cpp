#include "Vector.h"
#include "Ray.h"
#include <iostream>

int main()
{
	Vector org(0,0,0), dir(0,0,1);
	Ray ray(org,dir);

	std::cout << ray.getDirection().getX() ;

	system("pause");
	return 0;
}