#include"Cube.h"
int Cube::setPoint() {
	float tP[] = { -0.5,-0.5,-0.5,
		-0.5,-0.5,0.5,
		-0.5,0.5,0.5,
		-0.5,0.5,-0.5,
		0.5,-0.5,-0.5,
		0.5,-0.5,0.5,
		0.5,0.5,0.5,
		0.5,0.5,-0.5 };
	for (int i = 0; i < 24; i++)
		point3.push_back(tP[i]);
	return 0;
}
int Cube::setNormal() {
	float tP[] = { -0.5,-0.5,-0.5,
		-0.5,-0.5,0.5,
		-0.5,0.5,0.5,
		-0.5,0.5,-0.5,
		0.5,-0.5,-0.5,
		0.5,-0.5,0.5,
		0.5,0.5,0.5,
		0.5,0.5,-0.5 };
	for (int i = 0; i < 24; i++)
		point3.push_back(tP[i]);
	return 0;
}
int Cube::setTexCoord() {
	return 0;
}

int Cube::setDrawMethod() {
	drawMethod = GL_QUADS;
	return 0;
}