#include "Light.h"


int Light::count = 0;

Light::Light(const int type) {
	this->type = type;
	ID = count++;
}

Light::Light(const int type, const float pos[3], const float a[3], const float s[3], const float d[3]) {
	this->type = type;
	for (int i = 0; i < 3; i++) {
		this->postion[i] = pos[i];
		this->ambient[i] = a[i];
		this->specular[i] = s[i];
		this->diffuse[i] = d[i];
	}
	ID = count++;
}

Light::Light(const int type, const float pos[3], const float a[3], const float s[3], const float d[3],const float dir[3], const float c) {
	this->type = type;
	for (int i = 0; i < 3; i++) {
		this->postion[i] = pos[i];
		this->direction[i] = dir[i];
		this->ambient[i] = a[i];
		this->specular[i] = s[i];
		this->diffuse[i] = d[i];
	}
	this->cutoff = c;
	ID = count++;
}