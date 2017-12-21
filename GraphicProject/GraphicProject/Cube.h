#pragma once
#include"Object.h"
class Cube :public Object
{
public:
	Cube()
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