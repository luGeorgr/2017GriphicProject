#pragma once
#include"Object.h"
class Cube :public Object
{
public:
	Cube():Object(0)
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
};