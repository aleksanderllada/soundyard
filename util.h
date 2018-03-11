#pragma once
#include <math.h>
#include "hge.h"

struct point
{
	float x;
	float y;
	point(){ x=0; y=0; } //Origin
	point(float _x, float _y){ x=_x; y=_y; }
	point(double _x, double _y) { x=(float)_x; y=(float)_y; }
	point(int _x, int _y) { x=(float)_x; y=(float)_y; }
};

class circunference
{
private:
	point center;
	float radius;
	float A;
	float B;
	float C;
public:
	circunference(point _center, float _radius);
	bool TestPoint(point _point);					//Tests if a point lies inside the circunference
	const point GetCenter() { return center; }
	const float GetRadius() { return radius; }
};

float DistanceBetweenTwoPoints(point p1, point p2);