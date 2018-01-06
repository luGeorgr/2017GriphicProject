#pragma once

#include "Observable.h"
#include "Changes.h"
#include "Object.h"
#include "Cube.h"
#include "ObjByRead.h"
#include "Texture.h"

class Model : public Observable {  // 存放所有数据
private:
	vector<shared_ptr<Object> > ObjectList;
	vector<shared_ptr<Texture> > TexList;  // =====

	shared_ptr<Texture> findTexFromID(const int id) {
		if (id == -1) return NULL;
		for (vector<shared_ptr<Texture> >::iterator i = TexList.begin(); i != TexList.end(); i++) {
			if ((*i)->ID == id) return *i;
		}
	}

public:
	void AddObject(const vector<float>& floatParams, const vector<int>& intParams);
	void DrawOneObjectWithOneMethod(const vector<int>& intParams);
	shared_ptr<Object> GetObject(const vector<int>& intParams);
	shared_ptr<Object> GetLastObject();
	void ReadTex(const vector<string>& files, const vector<int>& types);
};
