#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	float x, y, z;
} Vector;
	
float magnitude (Vector& vect);
	
Vector normalize (Vector& vect);
	
Vector negative (Vector& vect);
	
float dotProduct(Vector& vect, Vector& v);
	
Vector crossProduct(Vector& vect, Vector& v);
	
Vector VectorAdd (Vector& vect, Vector& v);

Vector VectorMult (Vector& vect, float scalar);

#endif