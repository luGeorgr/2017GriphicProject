#include "BasicDraw.h"
void BasicDraw::LightSetting()
{
	for (int i = 0; i < lightList->size(); i++) {
		glEnable(GL_LIGHTING);
		Light* light = ((*lightList)[i]).get();
		GLenum GL_LIGHTX = getGL_LIGHTX(i);
		if (light->type != 2) {
			glLightfv(GL_LIGHTX, GL_POSITION, light->postion);
		}
		else {
			glLightfv(GL_LIGHTX, GL_POSITION, light->postion);
			glLightf(GL_LIGHTX, GL_SPOT_CUTOFF, light->cutoff);
			glLightfv(GL_LIGHTX, GL_SPOT_DIRECTION, light->direction);
		}

		glLightfv(GL_LIGHTX, GL_AMBIENT, light->ambient);
		glLightfv(GL_LIGHTX, GL_SPECULAR, light->specular);
		glLightfv(GL_LIGHTX, GL_DIFFUSE, light->diffuse);
		glEnable(GL_LIGHTX);
	}
}
int BasicDraw::DrawObject()
{
	LightSetting();
	glEnable(GL_COLOR_MATERIAL);
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
		glNormal3f(normal3[i], normal3[i + 1], normal3[i + 2]);
		glVertex3f(point3[i],point3[i+1],point3[i+2]);
	}
	glEnd();
	glPopMatrix();
	return 0;
}

void BasicDraw::Set(int drawMethod, float * color, float * position, float * scale, float * rotate, const vector<float>& point3, const vector<float>& normal3, const vector<float>& texCoord3,int id,
	vector<shared_ptr<Light>>*light)
{
	this->drawMethod = drawMethod;
	memcpy(this->color, color, sizeof(this->color));
	memcpy(this->position, position, sizeof(this->position));
	memcpy(this->scale, scale, sizeof(this->scale));
	memcpy(this->rotate, rotate, sizeof(this->rotate));
	this->point3 = point3;
	this->normal3 = normal3;
	this->texCoord3 = texCoord3;
	this->objectID = id;
	this->lightList = light;
}
