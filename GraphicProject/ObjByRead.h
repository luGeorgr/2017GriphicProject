#pragma once

#include "Object.h"
#include "ObjFile.h"

class ObjByRead : public Object {
private:
	int setPoint();
	int setNormal();
	int setTexCoord();
	int setDrawMethod();
	string file;

public:
	ObjByRead(string f) : Object(1) {
		this->file = f;
		setPoint();
		setNormal();
		setTexCoord();
		setDrawMethod();
	}
};
