#pragma once
#include"Object.h"
#include"ObjFile.h"

class ObjByRead :public Object {
private:
	int setPoint();
	int setNormal();
	int setTexCoord();
	int setDrawMethod();

public:
	ObjByRead() :Object(1) {
		setPoint();
		setNormal();
		setTexCoord();
		setDrawMethod();
	}
};