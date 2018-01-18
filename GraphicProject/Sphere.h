#pragma once
#include"Object.h"
#define PI 3.14159265358979323846
#define PI2 6.28318530717958647692
class Sphere :public Object
{
public:
	void GeneratorHitCube() {

		vector<Point> pv;
		for (int i = 0; i < point3.size(); i += 3)
		{
			pv.push_back(Point(point3[i], point3[i + 1], point3[i + 2]));
		}
		this->hitCubes.push_back(GenerateOBB(pv));
	}
	Sphere(float radius) :Object(0), radius(radius)
	{
		setPoint();
		setNormal();
		setTexCoord();
		setDrawMethod();
		GeneratorHitCube();
	}
private:
	int setPoint();
	int setNormal();
	int setTexCoord();
	int setDrawMethod();
	double radius;
	int uStepsNum = 50, vStepNum = 50;
	class roundPoint
	{
	public:
		roundPoint() {};
		roundPoint(double x, double y, double z, double normalx, double normaly, double normalz) :x(x), y(y), z(z), normalx(normalx), normaly(normaly), normalz(normalz) {};
	public:
		double x;
		double y;
		double z;
		double normalx;
		double normaly;
		double normalz;
	};
	//u is the angle with x, v
	roundPoint calPoint(double u, double v)
	{
		double sinv = sin(PI*v), cosv = cos(PI*v), sinu = sin(PI2*u), cosu = cos(PI2*u);
		double A = -2 * PI * PI * radius * radius * sinv;
		double x =  radius * sinv*cosu;
		double y =  radius * sinv*sinu;
		double z =  radius * cosv;
		double normalx = A * sinv * cosu;
		double normaly = A * sinv * sinu;
		double normalz = A * cosv;
		return roundPoint(x, y, z, normalx, normaly, normalz);
	}
};
