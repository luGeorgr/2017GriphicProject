#include "Cone.h"

int Cone::setPoint()
{
	double angle = 2 * PI / RoundStepNum;
	double x, y, z;
	double temp = 0;
	x = radius; y = 0; z = 0;
	for (int i = 0; i < RoundStepNum; i++) {
		point3.push_back(0); point3.push_back(0); point3.push_back(z);
		point3.push_back(x); point3.push_back(y); point3.push_back(z);
		temp += angle;
		x = radius * cos(temp);
		y = radius * sin(temp);
		point3.push_back(x); point3.push_back(y); point3.push_back(z);
	}

	temp = 0;
	double nextx, nexty;
	x = radius; y = 0; z = 0;
	for (int i = 0; i < RoundStepNum; i++) {
		point3.push_back(0); point3.push_back(0); point3.push_back(height);
		point3.push_back(x); point3.push_back(y); point3.push_back(0);
		temp += angle;
		nextx = radius * cos(temp);
		nexty = radius * sin(temp);
		point3.push_back(nextx); point3.push_back(nexty); point3.push_back(0);
		x = nextx;
		y = nexty;
	}
	return 0;
}

int Cone::setNormal()
{
	return 0;
}

int Cone::setTexCoord()
{
	return 0;
}

int Cone::setDrawMethod()
{
	return 0;
}
