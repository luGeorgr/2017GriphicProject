#pragma once
#include"Data.h"
class Draw {
protected:
	int drawMethod;
	float color[3];
	float position[3];
	float scale[3];//x y z
	float rotate[3];
	vector<float> point3;
	vector<float> normal3;
	vector<float> texCoord3;
	virtual int DrawObject();
};
