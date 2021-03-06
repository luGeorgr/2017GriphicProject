#pragma once

#include "Object.h"

class Cube : public Object {
public:
	void GeneratorHitCube() {

		vector<Point> pv;
		for (int i = 0; i < point3.size(); i += 3)
		{
			pv.push_back(Point(point3[i], point3[i + 1], point3[i + 2]));
		}
		this->hitCubes.push_back(GenerateOBB(pv));
	}
	Cube() : Object(0) {
		setPoint();  // override virtual function
		setNormal();  // override virtual function
		setTexCoord();  // override virtual function
		setDrawMethod();  // override virtual function
		GeneratorHitCube();
	}
private:
	int setPoint();
	int setNormal();
	int setTexCoord();
	int setDrawMethod();
};