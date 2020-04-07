#include "Vector2D.h"
#include <cmath>

//default constructor
Vector2D::Vector2D() {
}

//destructor
Vector2D::~Vector2D() {
}

//overloaded constructor
Vector2D::Vector2D(int eX, int eY) {
	X = eX;
	Y = eY;
}

//return magnitude of the vector
float Vector2D::magnitude() {
	return sqrtf(powf(X, 2) + powf(Y, 2));
}