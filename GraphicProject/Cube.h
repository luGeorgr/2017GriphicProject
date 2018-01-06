#pragma once

#include "Object.h"

class Cube : public Object {
public:
	Cube() : Object(0) {
		setPoint();  // override virtual function
		setNormal();  // override virtual function
		setTexCoord();  // override virtual function
		setDrawMethod();  // override virtual function
	}

private:
	int setPoint();
	int setNormal();
	int setTexCoord();
	int setDrawMethod();
};