#pragma once
#include"Object.h"
#include"ObjFile.h"

class ObjByRead :public Object {
private:
	int setPoint();
	int setNormal();
	int setTexCoord();
	int setDrawMethod(int m);
	string file;

public:
	ObjByRead(string f,int method) :Object(1) {
		this->file = f;
		setPoint();
		setNormal();
		setTexCoord();
		setDrawMethod(method);
	}
};