#include "util.h"

circunference::circunference(point _center, float _radius)
{
	center=_center;
	radius=_radius;
	A=(-2)*center.x;
	B=(-2)*center.y;
	C=pow(center.x, 2)+pow(center.y, 2)-pow(radius, 2);
}

bool circunference::TestPoint(point _point)
{
	float result;
	result=pow(_point.x, 2)+pow(_point.y, 2)+(A*_point.x)+(B*_point.y)+C;

	if(result<=0)
		return true;
	else
		return false;
}

float DistanceBetweenTwoPoints(point p1, point p2)
{
	float result;
	result=sqrt(pow((p1.x-p2.x), 2)+pow((p1.y-p2.y), 2));
	return result;
}