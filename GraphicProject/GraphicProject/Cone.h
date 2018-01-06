#pragma once
#include"Object.h"
#define PI 3.14159265358979323846
class Cone :public Object
{
public:
	Cone(float raduis, float height) :Object(0), radius(raduis), height(height)
	{
		setPoint();
		setNormal();
		setTexCoord();
		setDrawMethod();
	}
private:
	int RoundStepNum = 200;
	int setPoint();
	int setNormal();
	int setTexCoord();
	int setDrawMethod();
	float radius;
	float height;
};
