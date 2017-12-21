#pragma once
#include"Data.h"
#include<iterator>
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
public:
	virtual int DrawObject();
	void Set(int drawMethod, float* color, float* position, float* scale, float* rotate, const vector<float>& point3, const vector<float>& normal3, const vector<float>& texCoord3);
};
