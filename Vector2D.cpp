#include "Vector2D.hpp"

Vector2D::Vector2D(int iX, int iY) {
	x = iX;
	y = iY;
}

Vector2D::~Vector2D() {
	delete& x;
	delete& y;
	//Don't use just wanted to leave it in
	//delete this;
}

int Vector2D::getX() {
	return x;
}
int Vector2D::getY() {
	return y;
}

void Vector2D::setX(int nX) {
	x = nX;
}
void Vector2D::setY(int nY) {
	y = nY;
}