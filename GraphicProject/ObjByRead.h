#pragma once
#include"Object.h"
#include"ObjFile.h"
#include"Texture.h"
class ObjByRead :public Object {
private:
	int setPoint();
	int setNormal();
	int setTexCoord();
	int setDrawMethod();
	int setMaterial();
	int setIndex();
	int setTex();
	int setFace();
	string file;
	ObjFile *obj;
	vector<Material> material;
	vector<shared_ptr<Texture>> KaTexList;
	vector<shared_ptr<Texture>> KdTexList;
	vector<int> index;
	vector<int> face;
public:
	/*
	ObjByRead(string f,int method) :Object(1) {
	this->file = f;
	setPoint();
	setNormal();
	setTexCoord();
	setDrawMethod(method);
	}
	*/
	void GeneratorHitCube() {
		vector<Point> pv;
		int offset = 0;
		while (offset < obj->V.size())
		{
			if (!obj->V[offset].flag)
			{
				offset++;
				continue;
			}
			pv.clear();
			Point t = Point(obj->V[offset].x, obj->V[offset].y, obj->V[offset].z);
			for (int i = offset; i < obj->V.size(); i += 1)
			{
				if (obj->V[i].flag&&fabs(obj->V[i].x - t.x) < 10 && fabs(obj->V[i].y - t.y) < 10 && fabs(obj->V[i].z - t.z) < 10)
				{
					pv.push_back(Point(obj->V[i].x, obj->V[i].y, obj->V[i].z));
					obj->V[i].flag = false;
				}
			}
			this->hitCubes.push_back(GenerateOBB(pv));
			offset++;
		}
	}
	ObjByRead(string f) :Object(10) {
		this->file = f;
		obj = new ObjFile(this->file);
		setPoint();
		setNormal();
		setTexCoord();
		setDrawMethod();
		setIndex();
		setTex();
		setFace();
		GeneratorHitCube();
		//setMaterial();
		delete obj;
	}
	vector<shared_ptr<Texture>>& getKdTexList() { return KdTexList; }
	vector<shared_ptr<Texture>>& getKaTexList() { return KaTexList; }	
	vector<int>& getIndex() { return index; }
	vector<int>& getFace() { return face; }
};