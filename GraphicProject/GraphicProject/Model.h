#pragma once
#include"Observable.h"
#include"Changes.h"
#include"Object.h"
#include"Cube.h"
#include"ObjByRead.h"
class Model : public Observable
{
private:
	vector<shared_ptr<Object>>ObjectList;
public:
	void AddObject(const vector<float>& floatParams, const vector<int>& intParams);
	void DrawOneObjectWithOneMethod(const vector<int>& intParams);
	shared_ptr<Object> GetObject(const vector<int>& intParams);
	shared_ptr<Object> GetLastObject();
};

