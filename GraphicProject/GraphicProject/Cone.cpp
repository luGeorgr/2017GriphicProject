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

		normal3.push_back(0); normal3.push_back(0); normal3.push_back(-1);
		normal3.push_back(0); normal3.push_back(0); normal3.push_back(-1);
		normal3.push_back(0); normal3.push_back(0); normal3.push_back(-1);
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

		double l = x, m = y, n = -height;
		double o = nextx - x, p = nexty - y, q = 0;
		double fx = m * q - n * p, fy = n * o - l * q, fz = l * p - m * o;
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
		x = nextx;
		y = nexty;
	}
	return 0;
}

int Cone::setNormal()
{
	//done in set points
	return 0;
}

int Cone::setTexCoord()
{
	for (int i = RoundStepNum * 3; i < point3.size(); i++) {
		float x = point3[i], y = point3[i + 1], z = point3[i + 2];
		float u = acos(x / radius) / 2 / PI;
		float v = z / height;
		texCoord3.push_back(u);
		texCoord3.push_back(v);
	}
	return 0;
}

int Cone::setDrawMethod()
{
	return 0;
}
