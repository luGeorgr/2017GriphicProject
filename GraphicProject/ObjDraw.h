#pragma once
#include"BasicDraw.h"
#include "glext.h"
class ObjDraw :public BasicDraw{
public:
	ObjDraw() {}
	virtual int DrawObject();
	void setIndexandFace(const vector<int>& intParams);
	void setKdsize(int s);
	void setTextures(const vector<shared_ptr<Texture>>& texParams);
private:
	vector<int> indexAndFace;
	vector<shared_ptr<Texture>> textures;
	int Kdsize;
};