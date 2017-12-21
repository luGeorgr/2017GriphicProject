#pragma once
#include"Observable.h"
#include"Changes.h"
#include"Object.h"
#include"Cube.h"
class Model : public Observable
{
private:
	vector<shared_ptr<Object>>ObjectList;
public:
	void DrawCube(const vector<float>& floatParams);
	shared_ptr<Object> GetLastObject();
};

