#pragma once
class Vector2D {
public:
	Vector2D(int iX, int iY);
	~Vector2D();

	void setX(int nX);
	void setY(int nY);

	int getX();
	int getY();

private:
	int x;
	int y;
};