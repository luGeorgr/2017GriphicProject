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
	int v[3], t[3], n[3];
};

class ObjFile
{
public:


	vector<vertex> V;
	vector<tex> T;
	vector<normal> N;
	vector<face> F;
	ObjFile(string file);
private:

};


