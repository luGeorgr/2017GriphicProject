#include "Trustum.h"

int Trustum::setPoint()
{
	float angle = 2 * PI / numOfFace;
	double x, y, z;
	double temp = 0;
	double newRadius = radius * ratio;
	x = radius; y = 0; z = 0;
	for (int i = 0; i < numOfFace; i++) {
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
	double ax, ay, az, bx, by, bz, cx, cy, cz, dx, dy, dz;
	for (int i = 0; i < numOfFace; i++) {
		ax = radius * cos(temp); ay = radius * sin(temp); az = 0;
		bx = newRadius * cos(temp); by = newRadius * sin(temp); bz = height;
		temp += angle;
		cx = newRadius * cos(temp); cy = newRadius * sin(temp); cz = height;
		dx = radius * cos(temp); dy = radius * sin(temp); dz = 0;
		point3.push_back(ax); point3.push_back(ay); point3.push_back(az);
		point3.push_back(bx); point3.push_back(by); point3.push_back(bz);
		point3.push_back(cx); point3.push_back(cy); point3.push_back(cz);

		point3.push_back(cx); point3.push_back(cy); point3.push_back(cz);
		point3.push_back(dx); point3.push_back(dy); point3.push_back(dz);
		point3.push_back(ax); point3.push_back(ay); point3.push_back(az);

		double l = cx - bx, m = cy - by, n = cz - bz;
		double o = ax - bx, p = ay - by, q = az - bz;
		double fx = m * q - n * p, fy = n * o - l * q, fz = l * p - m * o;
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
		normal3.push_back(fx); normal3.push_back(fy); normal3.push_back(fz);
	}
	x = newRadius; y = 0; z = height;
	for (int i = 0; i < numOfFace; i++) {
		point3.push_back(0); point3.push_back(0); point3.push_back(z);
		point3.push_back(x); point3.push_back(y); point3.push_back(z);
		temp += angle;
		x = newRadius * cos(temp);
		y = newRadius * sin(temp);
		point3.push_back(x); point3.push_back(y); point3.push_back(z);

		normal3.push_back(0); normal3.push_back(0); normal3.push_back(1);
		normal3.push_back(0); normal3.push_back(0); normal3.push_back(1);
		normal3.push_back(0); normal3.push_back(0); normal3.push_back(1);
	}
	return 0;
}

int Trustum::setNormal()
{
	//done in set points
	return 0;
}

int Trustum::setTexCoord()
{
	return 0;
}

int Trustum::setDrawMethod()
{
	return 0;
}
