#pragma once

#include "Observable.h"
#include "Changes.h"
#include "Object.h"
#include "Cube.h"
#include "ObjByRead.h"
#include "Texture.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Prism.h"
#include "HitCheck.h"
#include "Light.h"
class Model : public Observable {  // 存放所有数据
private:
	  // =====
	shared_ptr<Object> findObjectFromID(const int id){
		if (id < 0)return nullptr;
		for (auto i : ObjectList)
			if (i->getID() == id)
				return i;
		return nullptr;
	}
	
	shared_ptr<Texture> findTexFromID(const int id) {
		if (id == -1) return NULL;
		for (vector<shared_ptr<Texture> >::iterator i = TexList.begin(); i != TexList.end(); i++) {
			if ((*i)->ID == id) return *i;
		}
	}

public:
	vector<shared_ptr<Object> > ObjectList;
	vector<shared_ptr<Light>> LightList;
	vector<shared_ptr<Texture> > TexList;
	void AdjustObject(const vector<float>& floatParams, const vector<int>& intParams);
	void AddObject(const vector<float>& floatParams, const vector<int>& intParams, const vector<string>& stringParams);
	void DrawOneObjectWithOneMethod(const vector<int>& intParams);
	void DrawOneobj(const vector<int>& intParams);
	shared_ptr<Object> GetObject(const vector<int>& intParams);
	shared_ptr<Object> GetLastObject();
	void ReadTex(const vector<string>& files, const vector<int>& types);
	void  ObjectMove();
	void AddOrDeleteLight(const vector<float>& floatParams, const vector<int>& intParams);
	void SetObjectAttribute(const vector<float>& floatParams, const vector<int>& intParams);
	shared_ptr<Light> findLightFromID(const int id) {
		if (id < 0)return nullptr;
		for (auto i : LightList)
			if (i->ID == id)
				return i;
		return nullptr;
	}
};
