#pragma once
#include "Light.h"
#include "Data.h"
#include <iterator>

class BasicDraw {
protected:
	int drawMethod;
	float color[3];
	float position[3];
	float scale[3];  // x y z
	float rotate[3];
	vector<float> point3;
	vector<float> normal3;
	vector<float> texCoord3;
	int objectID;
	
	//π‚’’

	vector<shared_ptr<Light>>* lightList;
	void LightSetting();
	GLenum getGL_LIGHTX(int i) {
		switch (i) {
		case 0:return GL_LIGHT0;
		case 1:return GL_LIGHT1;
		case 2:return GL_LIGHT2;
		case 3:return GL_LIGHT3;
		case 4:return GL_LIGHT4;
		case 5:return GL_LIGHT5;
		case 6:return GL_LIGHT6;
		case 7:return GL_LIGHT7;
		}
	}
public:
	BasicDraw() {}
	int getID() { return objectID; }
	void setPosition(float x, float y, float z) {
		position[0] = x;
		position[1] = y;
		position[2] = z;
	}

	void setColor(float x, float y, float z) {
		color[0] = x;
		color[1] = y;
		color[2] = z;
	}

	void setScale(float x, float y, float z) {
		scale[0] = x;
		scale[1] = y;
		scale[2] = z;
	}

	void setRotate(float x, float y, float z) {
		rotate[0] = x;
		rotate[1] = y;
		rotate[2] = z;
	}
	virtual int DrawObject();
	void Set(int drawMethod, float* color, float* position, float* scale, float* rotate,
		const vector<float>& point3, const vector<float>& normal3, const vector<float>& texCoord3, int id,
		vector<shared_ptr<Light>>*light);
};
