#pragma once
#include<stdlib.h>
#include<string>
#include<iostream>
#include<gl/glut.h>
#include<vector>
#include"Object.h"


using namespace std;

struct vertex
{
	float x, y, z;
	bool flag=true;
};

struct tex
{
	float tu, tv;
};
struct normal
{
	float x, y, z;
};
struct face
{
	int type;
	int* v;
	int* t;
	int* n;
	int m_index;
};

struct Material {
	int index;
	string name;
	float Ns=0;
	float Ni=0;
	float d=0;
	float Tr=0;
	float Tf[3];
	int illum=0;
	float Ka[3];
	float Kd[3];
	float Ks[3];
	float Ke[3];
	string map_Ka;
	string map_Kd;
	
	string map_Ks;
	string map_Bump;
	string map_d ;
	string Bump;

};

class ObjFile
{
public:


	vector<vertex> V;
	vector<tex> T;
	vector<normal> N;
	vector<face> F;
	vector<Material> M;
	ObjFile(string file);
private:
	void ReadMTLData(string file, Material* material);
	int ReadMTLFile(string file);
};


