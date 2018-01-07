#pragma once
#include"Object.h"
#define PI 3.14159265358979323846

class Trustum :public Object
{
public:
	//棱台高度， 上下面边之比;
	Trustum(int numOfFace, float raduis, float height, float ratio) :Object(0), numOfFace(numOfFace), radius(raduis), height(height), ratio(ratio)
	{
		setPoint();
		setNormal();
		setTexCoord();
		setDrawMethod();
	}
private:
	int setPoint();
	int setNormal();
	int setTexCoord();
	int setDrawMethod();
	int numOfFace;
	float radius;
	float height;
	float ratio;
};