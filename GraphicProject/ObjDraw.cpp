#include "ObjDraw.h"

extern PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
extern PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
int ObjDraw::DrawObject()
{
	glDisable(GL_COLOR_MATERIAL);
	LightSetting();
	/*if (false && textures.size() > Kdsize)//mix
	{
		glPushMatrix();
		glColor3fv(color);
		glTranslatef(position[0], position[1], position[2]);
		glScalef(scale[0], scale[1], scale[2]);
		glRotatef(rotate[0], 1, 0, 0);
		glRotatef(rotate[1], 0, 1, 0);
		glRotatef(rotate[2], 0, 0, 1);
		for (int i = 0; i < point3.size(); i += 9) {
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[index[i / 9]]->texture);
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[index[i / 9]+Kdsize]->texture);
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glBegin(GL_TRIANGLES);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, texCoord3[i / 3 * 2], texCoord3[i / 3 * 2 + 1]);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, texCoord3[i / 3 * 2 + 2], texCoord3[i / 3 * 2 + 3]);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, texCoord3[i / 3 * 2 + 4], texCoord3[i / 3 * 2 + 5]);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, texCoord3[i / 3 * 2], texCoord3[i / 3 * 2 + 1]);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, texCoord3[i / 3 * 2 + 2], texCoord3[i / 3 * 2 + 3]);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, texCoord3[i / 3 * 2 + 4], texCoord3[i / 3 * 2 + 5]);
			glVertex3f(point3[i], point3[i + 1], point3[i + 2]);
			glVertex3f(point3[i + 3], point3[i + 4], point3[i + 5]);
			glVertex3f(point3[i + 6], point3[i + 7], point3[i + 8]);
			glEnd();
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glDisable(GL_TEXTURE_2D);
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glDisable(GL_TEXTURE_2D);
		}
		glPopMatrix();
	}
	else*/
	{
		glPushMatrix();
		glColor3fv(color);
		glTranslatef(position[0], position[1], position[2]);
		glScalef(scale[0], scale[1], scale[2]);
		glRotatef(rotate[0], 1, 0, 0);
		glRotatef(rotate[1], 0, 1, 0);
		glRotatef(rotate[2], 0, 0, 1);
		//glEnable(GL_COLOR_MATERIAL);
		Texture* t;
		float clear[3]{ 0,0,0 };
		int offset1 = 0, offset2 = 0;
		int total = indexAndFace.size() / 2;
		for (int i = 0; i < total; i += 1) {
			t = textures[indexAndFace[2*i]].get();
			if (t->ID >= 0)
			{
				glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glBindTexture(GL_TEXTURE_2D, t->texture);
			}
			glMaterialfv(GL_FRONT, GL_DIFFUSE, t->Kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, t->Ks);
			glMaterialfv(GL_FRONT, GL_AMBIENT, t->Ka);
			glMaterialfv(GL_FRONT, GL_EMISSION, t->Ke);
			glBegin(GL_POLYGON);
			for (int j = 0; j < indexAndFace[2*i + 1]; j++) {
				glNormal3f(normal3[offset2], normal3[offset2 + 1], normal3[offset2 + 2]);
				glTexCoord2f(texCoord3[offset1], texCoord3[offset1 + 1]);
				glVertex3f(point3[offset2], point3[offset2 + 1], point3[offset2 + 2]);
				offset1 += 2;
				offset2 += 3;
			}
			glEnd();
			
			glMaterialfv(GL_FRONT, GL_DIFFUSE,clear);
			glMaterialfv(GL_FRONT, GL_SPECULAR, clear);
			glMaterialfv(GL_FRONT, GL_AMBIENT, clear);
			glMaterialfv(GL_FRONT, GL_EMISSION, clear);
		}
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();		
	}
	return 0;
}

void ObjDraw::setIndexandFace(const vector<int>& intParams)
{
	indexAndFace = intParams;
}

void ObjDraw::setKdsize(int s)
{
	Kdsize = s;
}

void ObjDraw::setTextures(const vector<shared_ptr<Texture>>& texParams)
{
	textures = texParams;
}
