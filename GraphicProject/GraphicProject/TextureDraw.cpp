#include "TextureDraw.h"

int TextureDraw::DrawObject()
{
	unsigned long mode;
	if (textureMethod == 2) {  // mixed
		if (textures.size() < 2) {
			return -1;  // error
		}
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[0].texture);
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[1].texture);
	}
	else {
		if (textures.size() < 1) {
			return -1;  // error
		}
		if (textureMethod == 0)  // 2d
			mode = GL_TEXTURE_2D;
		else if (textureMethod == 1)  // 1d
			mode = GL_TEXTURE_1D;
		glEnable(GL_COLOR_MATERIAL);
		glEnable(mode);
		glBindTexture(mode, textures[0].texture);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	glPushMatrix();
	glColor3fv(color);
	glTranslatef(position[0], position[1], position[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotate[0], 1, 0, 0);
	glRotatef(rotate[1], 0, 1, 0);
	glRotatef(rotate[2], 0, 0, 1);
	glBegin(drawMethod);
	for (int i = 0; i < point3.size(); i += 3) {
		if (textureMethod == 0)  // 2d
			glTexCoord2i(texCoord3[i], texCoord3[i + 1]);
		else if (textureMethod == 1)  // 1d
			glTexCoord1i(texCoord3[i]);
		else if (textureMethod == 2) {  // mixed
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, texCoord3[i], texCoord3[i + 1]);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, texCoord3[i], texCoord3[i + 1]);
		}
		glVertex3f(point3[i], point3[i + 1], point3[i + 2]);
	}
	glEnd();
	glPopMatrix();
	if (textureMethod == 0 || textureMethod == 1)
		glDisable(mode);
	else {
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glDisable(GL_TEXTURE_2D);
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glDisable(GL_TEXTURE_2D);
	}
	return 0;
}
