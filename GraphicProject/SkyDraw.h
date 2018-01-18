#pragma once
#include"BasicDraw.h"

class SkyDraw :public BasicDraw {
private:
	vector<Texture> textures;
	float width = 5000;
	float height = 5000;
	float length = 5000;
	float x = -2000, y = -2000, z = -2000;
public:
	SkyDraw() {
		textures.push_back(Texture("sky\\back.jpg", 0, 1));
		textures.push_back(Texture("sky\\front.jpg", 0, 1));
		textures.push_back(Texture("sky\\bottom.png", 0, 1));
		textures.push_back(Texture("sky\\top.jpg", 0, 1));
		textures.push_back(Texture("sky\\left.jpg", 0, 1));
		textures.push_back(Texture("sky\\right.jpg", 0, 1));
		for (int i = 0; i < 6; i++)
			textures[i].bindTex();
	}
	virtual int DrawObject() {
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glTranslatef(-x, -y, -z);
		glBindTexture(GL_TEXTURE_2D, textures[0].texture);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + height);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z + height);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[1].texture);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + length, z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + length, z + height);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + length, z + height);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + length, z);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[2].texture);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + length, z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + length, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[3].texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + height);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + length, z + height);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + length, z + height);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + height);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[4].texture);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[5].texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
		glEnd();
		glPopMatrix();
		glEnable(GL_LIGHTING);
		return 0;
	}
};