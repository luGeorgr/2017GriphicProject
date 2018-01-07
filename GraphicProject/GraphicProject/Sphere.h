#pragma once
#include"Object.h"
#define PI 3.14159265358979323846
#define PI2 6.28318530717958647692
class Sphere :public Object
{
public:
	Sphere(float raduis) :Object(0), radius(radius)
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
	double radius;
	int uStepsNum = 50, vStepNum = 50;
	class Point
	{
	public:
		Point() {};
		Point(double x, double y, double z, double normalx, double normaly, double normalz) :x(x), y(y), z(z), normalx(normalx), normaly(normaly), normalz(normalz) {};
	public:
		double x;
		double y;
		double z;
		double normalx;
		double normaly;
		double normalz;
	};
	//u is the angle with x, v
	Point calPoint(double u, double v)
	{
		double sinv = sin(PI*v), cosv = cos(PI*v), sinu = sin(PI2*u), cosu = cos(PI2*u);
		double A = -2 * PI * PI * radius * radius * sinv;
		double x = sinv*cosu;
		double y = sinv*sinu;
		double z = cosv;
		double normalx = A * sinv * cosu;
		double normaly = A * sinv * sinu;
		double normalz = A * cosv;
		return Point(x, y, z, normalx, normaly, normalz);
	}
};
