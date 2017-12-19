#pragma once
#include"Data.h"
class Object
{
public:
	Object();
	~Object();
	int getID() { return ID; }
	vector<float>& getPoint() { return point3; }
	vector<float>& getNormal() { return normal3; }
	vector<float>& gettexCoord() { return texCoord3; }
	float* getColor() { return color; }
	float* getPosition() { return position; }
	float* getScale() { return scale; }
	float* getRotate() { return rotate; }
	int setColor(float* input) { for (int i = 0; i < 3; i++) { color[i] = input[i]; } }
	int setPosition(float* input) { for (int i = 0; i < 3; i++) { position[i] = input[i]; } }
	int setScale(float* input) { for (int i = 0; i < 3; i++) { scale[i] = input[i]; } }
	int setRotate(float* input) { for (int i = 0; i < 3; i++) { rotate[i] = input[i]; } }
protected:
	static int count;
	int ID;
	int drawMethod;//GL_QUADS...
	float color[3] = {255};
	float position[3] = {0};
	float scale[3] = {1};//x y z
	float rotate[3] = {0};
	vector<float> point3;
	vector<float> normal3;
	vector<float> texCoord3;
	virtual int setPoint() = 0;
	virtual int setNormal() = 0;
	virtual int setTexCoord() = 0;
	virtual int setDrawMethod() = 0;
};

Object::Object()
{
	ID = count++;
	setPoint();
	setNormal();
	setTexCoord();
	setDrawMethod();
}

Object::~Object()
{
}

int Object::count = 0;