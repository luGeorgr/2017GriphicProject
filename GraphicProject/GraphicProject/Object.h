#pragma once
#include"Data.h"
class Object
{
public:
	Object(int type);
	~Object();
	int getID() { return ID; }
	int getDrawMethod() { return drawMethod; }
	vector<float>& getPoint() { return point3; }
	vector<float>& getNormal() { return normal3; }
	vector<float>& gettexCoord() { return texCoord3; }
	float* getColor() { return color; }
	float* getPosition() { return position; }
	float* getScale() { return scale; }
	float* getRotate() { return rotate; }
	void setColor(float R, float G, float B) {	color[0] = R; color[1] = G;	color[2] = B;}
	void setPosition(float x, float y, float z) { position[0] = x; position[1] = y; position[2] = z; }
	void setScale(float xScale, float yScale, float zScale) { scale[0] = xScale; scale[1] = yScale; scale[2] = zScale; }
	void setRotate(float xRotate, float yRotate, float zRotate) { rotate[0] = xRotate; rotate[1] = yRotate; rotate[2] = zRotate; }
	

	virtual int setPoint() = 0;
	virtual int setNormal() = 0;
	virtual int setTexCoord() = 0;
	virtual int setDrawMethod() = 0;
protected:
	static int count;
	int type;
	int ID;
	int drawMethod;//GL_QUADS...
	float color[3] = {0};
	float position[3] = {0};
	float scale[3] = {1};//x y z
	float rotate[3] = {0};
	vector<float> point3;
	vector<float> normal3;
	vector<float> texCoord3;
};
