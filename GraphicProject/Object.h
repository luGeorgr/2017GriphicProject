#pragma once

#include<fstream>
#include<sstream>
#include "Data.h"
#include "HitCheck.h"
class Object {
public:
	Object(int type);
	~Object();
	int getID() { return ID; }
	int getType() { return type; }
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
	virtual void GeneratorHitCube() = 0;
	void setObjectAttribute(boolean canMove = false, float vx = 0, float vy = 0, float vz = 0, float ax = 0, float ay = 0, float az = 0, float maxvx = 0, float maxvy = 0, float maxvz = 0) {
		this->vx = vx;
		this->vy = vy;
		this->vz = vz;
		this->ax = ax;
		this->ay = ay;
		this->az = az;
		this->maxvx = maxvx;
		this->maxvy = maxvy;
		this->maxvz = maxvz;
		this->canMove = canMove;
	}
	void ChangeVx() {
		if (vx + ax > maxvx)
			vx = maxvx;
		else 
			this->vx += this->ax;
	}
	void ChangeVy() {
		if (vy + ay > maxvy)
			vy = maxvy;
		else 
			this->vy += this->ay;
	}
	void ChangeVz() {
		if (vz + az > maxvz)
			vz = maxvz;
		else 
			this->vz += this->az;
	}
	void ChangeAllV() {
		ChangeVx();
		ChangeVy();
		ChangeVz();
	}

	void PreMove(float t){
		nextPosition[0] = position[0] + vx * t;
		nextPosition[1] = position[1] + vy * t;
		nextPosition[2] = position[2] + vz * t;
	}

	void Confirm(void) {
		for (int i = 0; i < 3; i++)
			position[i] = nextPosition[i];
	}

	float* getNextPosition() {
		return nextPosition;
	}

	bool MoveAbility() { 
		return (canMove || (vx != 0.0) || (vy != 0.0) || (vz != 0.0));
	}

	bool CanMove() {
		return canMove;
	}
	vector<HitCube> hitCubes;

	void SetV(float vx, float vy, float vz) {
		this->vx = vx;
		this->vy = vy;
		this->vz = vz;
	}
	void toFile(string filename);
protected:
	static int count;  // count objects of the same type
	int type;
	int ID;
	int drawMethod;  // GL_QUADS...
	float color[3] = {0, 0, 0};
	float position[3] = {0, 0, 0};
	float scale[3] = {1, 1, 1};  // x y z
	float rotate[3] = {0, 0, 0};
	vector<float> point3;
	vector<float> normal3;
	vector<float> texCoord3;
public:
	float nextPosition[3] = { 0, 0, 0 };
	float vx, vy, vz;
	float ax, ay, az;
	float maxvx, maxvy, maxvz;
	bool canMove;
};
