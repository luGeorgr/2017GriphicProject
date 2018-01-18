#pragma once
#include"Object.h"
#define PI 3.14159265358979323846
class Cone :public Object
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
	Cone(float raduis, float height) :Object(0), radius(raduis), height(height)
	{
		setPoint();
		setNormal();
		setTexCoord();
		setDrawMethod();
		GeneratorHitCube();
	}

private:
	int RoundStepNum = 200;
	int setPoint();
	int setNormal();
	int setTexCoord();
	int setDrawMethod();
	float radius;
	float height;
};
