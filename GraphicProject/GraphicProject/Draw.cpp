#include "Draw.h"
int Draw::DrawObject()
{
	glColor3fv(color);
	glPushMatrix();
	glTranslatef(position[0], position[1], position[3]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotate[0], 1, 0, 0);
	glRotatef(rotate[1], 0, 1, 0);
	glRotatef(rotate[2], 0, 0, 1);
	float *buffer1 = new GLfloat[sizeof(point3)];
	memcpy(buffer1, point3.data(), point3.size() * sizeof(float));
	float *buffer2 = new GLfloat[sizeof(normal3)];
	memcpy(buffer2, normal3.data(), normal3.size() * sizeof(float));
	glBegin(drawMethod);
	glVertex3fv(buffer1);
	glNormal3fv(buffer2);
	glEnd();
	glPopMatrix();
	return 0;
}

void Draw::Set(int drawMethod, float * color, float * position, float * scale, float * rotate, const vector<float>& point3, const vector<float>& normal3, const vector<float>& texCoord3)
{
	this->drawMethod = drawMethod;
	memcpy(this->color, color, sizeof(this->color));
	memcpy(this->position, position, sizeof(this->position));
	memcpy(this->scale, scale, sizeof(this->scale));
	memcpy(this->rotate, rotate, sizeof(this->rotate));
	this->point3 = point3;
	this->normal3 = normal3;
	this->texCoord3 = texCoord3;
}
