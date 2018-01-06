#include "BasicDraw.h"
int BasicDraw::DrawObject()
{
	glPushMatrix();
	glColor3fv(color);
	glTranslatef(position[0], position[1], position[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotate[0], 1, 0, 0);
	glRotatef(rotate[1], 0, 1, 0);
	glRotatef(rotate[2], 0, 0, 1);
	glBegin(drawMethod);
	for (int i = 0; i < point3.size(); i+=3)
	{
		glVertex3f(point3[i],point3[i+1],point3[i+2]);
	}
	glEnd();
	glPopMatrix();
	return 0;
}

void BasicDraw::Set(int drawMethod, float * color, float * position, float * scale, float * rotate, const vector<float>& point3, const vector<float>& normal3, const vector<float>& texCoord3)
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
