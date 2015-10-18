#include "Triangle.h"

#define EPSILON 0.000001

Triangle::Triangle(Vector a, Vector b, Vector c, Color color) : A(a), B(b), C(c), color(color)
{
	edge_1 = B.VectorAdd(A.Negative());
	edge_2 = A.VectorAdd(C.Negative());
}

Vector Triangle::getNormalAtPos(Vector& vect)
{
	Vector normal = edge_1.CrossProduct(edge_2).Normalize();

	return normal;
}

/* Möller-Trumbore intersection algorithm */
double Triangle::findIntersection(Ray& ray)
{
	Vector P, Q, T;
	double det, inv_det, u, v;
	double t;
	// Begin calculating determinant
	P = ray.getDirection().CrossProduct(edge_2);
	// If determinant is near zero, ray lies in plane of triangle
	det = edge_1.DotProduct(P);
	// NOT CULLING
	if(det > -EPSILON && det < EPSILON) return 0;
	
	inv_det = 1.f / det;
	// Calculate distance from V1 to ray origin
	T = ray.getOrigin().VectorAdd(A.Negative());
	// Calculate u parameter and test bound
	u = T.DotProduct(P) * inv_det;
	// Intersection lies outside of the triangle
	if(u < 0.f || u > 1.f) return 0;
	// Prepare to test v parameter
	Q = T.CrossProduct(edge_1);
	// Calculate V parameter and test bound
	v = ray.getDirection().DotProduct(Q) * inv_det;
	// Intersection lies outside of the triangle
	if(v < 0.f || u + v  > 1.f) return 0;

	t = edge_2.DotProduct(Q) * inv_det;

	if ( t > EPSILON )
		return t;

	return 0;
}