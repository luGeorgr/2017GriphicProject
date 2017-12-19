#include "Draw.h"
int Draw::DrawObject()
{
	glColor3fv(color);
	glTranslatef(position[0], position[1], position[3]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotate[0], 1, 0, 0);
	glRotatef(rotate[1], 0, 1, 0);
	glRotatef(rotate[2], 0, 0, 1);
	float *buffer1 = new GLfloat[sizeof(point3)];
	memcpy(buffer1, point3.data, point3.size() * sizeof(float));
	float *buffer2 = new GLfloat[sizeof(normal3)];
	memcpy(buffer2, normal3.data, normal3.size() * sizeof(float));
	glBegin(drawMethod);
	glVertex3fv(buffer1);
	glNormal3fv(buffer2);
	glEnd();
	return 0;
}
