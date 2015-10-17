#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	double x, y, z;
} Vector;
	
double magnitude (Vector* vect);
	
Vector normalize (Vector* vect);
	
Vector negative (Vector* vect);
	
double dotProduct(Vector* vect, Vector* v);
	
Vector crossProduct(Vector* vect, Vector* v);
	
Vector VectorAdd (Vector* vect, Vector* v);

Vector VectorMult (Vector* vect, double scalar);

#endif
