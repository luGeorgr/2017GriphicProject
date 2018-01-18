#pragma once



class Light {
public:
	static int count;
	int ID;
	int type;// 0:点光源 1:平行光源 2:聚光光源
	float postion[3] = { 0 };
	float ambient[3] = { 0 };
	float specular[3] = { 0 };
	float diffuse[3] = { 0 };
	float direction[3] = { 0 };
	float cutoff = 0;
	Light(const int type);
	Light(const int type, const float pos[3], const float a[3], const float s[3], const float d[3]);
	Light(const int type,const float pos[3], const float a[3], const float s[3], const float d[3], const float dir[3], const float c);
	~Light() {};




};