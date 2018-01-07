#include "Prism.h"

int Prism::setPoint()
{
	float angle = 2 * PI / numOfFace;
	double x, y, z;
	double temp = 0;
	x = radius; y = 0; z = 0;
	for (int i = 0; i < numOfFace; i++) {
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

	temp = 0;
	x = radius; y = 0; z = 0;
	double nextx, nexty;
	for (int i = 0; i < numOfFace; i++) {
		temp += angle;
		nextx = radius * cos(temp);
		nexty = radius * sin(temp);
		point3.push_back(x); point3.push_back(y); point3.push_back(0);
		point3.push_back(nextx); point3.push_back(nexty); point3.push_back(0);
		point3.push_back(nextx); point3.push_back(nexty); point3.push_back(height);

		point3.push_back(nextx); point3.push_back(nexty); point3.push_back(height);
		point3.push_back(x); point3.push_back(y); point3.push_back(height);
		point3.push_back(x); point3.push_back(y); point3.push_back(0);
		x = nextx;
		y = nexty;


		double l = nextx - x, m = nexty - y, n = 0;
		double o = 0, p = 0, q = height;
		double fx = m * q - n * p, fy = n * o - l * q, fz = l * p - m * o;
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
	}


	temp = 0;
	x = radius; y = 0; z = height;
	for (int i = 0; i < numOfFace; i++) {
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

int Prism::setNormal()
{
	//done in set points
	return 0;
}

int Prism::setTexCoord()
{
	for (int i = numOfFace * 3; i < point3.size() - numOfFace * 3; i++) {
		float x = point3[i], y = point3[i + 1], z = point3[i + 2];
		float u = acos(x / radius) / 2 / PI;
		float v = z / height;
		texCoord3.push_back(u);
		texCoord3.push_back(v);
	}
	return 0;
	return 0;
}

int Prism::setDrawMethod()
{
	drawMethod = GL_TRIANGLES;
	return 0;
}
