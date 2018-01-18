#include "Cylinder.h"

int Cylinder::setPoint()
{
	double angle = 2 * PI / RoundStepNum;
	double x, y, z;
	double temp = 0;
	x = radius; y = 0; z = 0;
	for (int i = 0; i < RoundStepNum; i++) {
		point3.push_back(0); point3.push_back(0); point3.push_back(z);
		normal3.push_back(0); normal3.push_back(0); normal3.push_back(-1);
		point3.push_back(x); point3.push_back(y); point3.push_back(z);
		normal3.push_back(0); normal3.push_back(0); normal3.push_back(-1);
		temp += angle;
		x = radius * cos(temp);
		y = radius * sin(temp);
		point3.push_back(x); point3.push_back(y); point3.push_back(z);
		normal3.push_back(0); normal3.push_back(0); normal3.push_back(-1);
	}
	x = radius; y = 0; z = 0;
	temp = 0;
	double nextx, nexty, nextz = height;
	for (int i = 0; i < RoundStepNum; i++) {
		temp += angle;
		nextx = radius * cos(temp);
		nexty = radius * sin(temp);
		point3.push_back(x); point3.push_back(y); point3.push_back(z);
		normal3.push_back(x); normal3.push_back(y); normal3.push_back(z);
		point3.push_back(nextx); point3.push_back(nexty); point3.push_back(z);
		normal3.push_back(nextx); normal3.push_back(nexty); normal3.push_back(z);
		point3.push_back(nextx); point3.push_back(nexty); point3.push_back(nextz);
		normal3.push_back(nextx); normal3.push_back(nexty); normal3.push_back(nextz);

		point3.push_back(nextx); point3.push_back(nexty); point3.push_back(nextz);
		normal3.push_back(nextx); normal3.push_back(nexty); normal3.push_back(nextz);
		point3.push_back(x); point3.push_back(y); point3.push_back(nextz);
		normal3.push_back(x); normal3.push_back(y); normal3.push_back(nextz);
		point3.push_back(x); point3.push_back(y); point3.push_back(z);
		normal3.push_back(x); normal3.push_back(y); normal3.push_back(z);
		x = nextx;
		y = nexty;
	}

	temp = 0;
	x = radius; y = 0; z = height;
	for (int i = 0; i < RoundStepNum; i++) {
		point3.push_back(0); point3.push_back(0); point3.push_back(z);
		normal3.push_back(0); normal3.push_back(0); normal3.push_back(1);
		point3.push_back(x); point3.push_back(y); point3.push_back(z);
		normal3.push_back(0); normal3.push_back(0); normal3.push_back(1);
		temp += angle;
		x = radius * cos(temp);
		y = radius * sin(temp);
		point3.push_back(x); point3.push_back(y); point3.push_back(z);
		normal3.push_back(0); normal3.push_back(0); normal3.push_back(1);
	}
	return 0;
}

int Cylinder::setNormal()
{
	//write in setPoint
	return 0;
}

int Cylinder::setTexCoord()
{
	for (int i = RoundStepNum * 3; i < point3.size() - RoundStepNum * 3; i++) {
		float x = point3[i], y = point3[i + 1], z = point3[i + 2];
		float u = acos(x / radius) / 2 / PI;
		float v = z / height;
		texCoord3.push_back(u);
		texCoord3.push_back(v);
	}
	return 0;
}

int Cylinder::setDrawMethod()
{
	drawMethod = GL_TRIANGLES;
	return 0;
}
