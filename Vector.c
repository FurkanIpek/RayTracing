#include "Vector.h"
#include <cmath>
	
float magnitude (Vector& vect) 
{
	return sqrt((vect.x*vect.x) + (vect.y*vect.y) + (vect.z*vect.z));
}
	
Vector normalize (Vector& vect) 
{
	float magnitude = sqrt((vect.x*vect.x) + (vect.y*vect.y) + (vect.z*vect.z));
	Vector normal;
	normal.x = -vect.x;
	normal.y = -vect.y;
	normal.z = -vect.z;
	return normal;
}
	
Vector negative (Vector& vect) 
{
	Vector neg_vec;
	neg_vec.x = -vect.x;
	neg_vec.y = -vect.y;
	neg_vec.z = -vect.z;
	return neg_vec;
}
	
float dotProduct(Vector& vect, Vector& v) 
{
	return vect.x*v.x + vect.y*v.y + vect.z*v.z;
}
	
Vector crossProduct(Vector& vect, Vector& v) 
{
	Vector cross_prod;
	cross_prod.x = vect.y*v.z - vect.z*v.y;
	cross_prod.y = vect.z*v.x - vect.x*v.z;
	cross_prod.z = vect.x*v.y - vect.y*v.x;
	return cross_prod;
}
	
Vector VectorAdd (Vector& vect, Vector& v) 
{
	Vector addition;
	addition.x = vect.x + v.x;
	addition.y = vect.y + v.y;
	addition.z = vect.z + v.z;
	return addition;
}

Vector VectorMult (Vector& vect, float scalar) 
{
	Vector multiplied;
	multiplied.x = vect.x * scalar;
	multiplied.y = vect.y * scalar;
	multiplied.z = vect.z * scalar;
	return multiplied;
}