#pragma once
#include "BasicDraw.h"
#include "Texture.h"
#include "glext.h"
PFNGLACTIVETEXTUREARBPROC glActiveTextureARB = NULL;
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB = NULL;

class TextureDraw : public BasicDraw {
public:
	TextureDraw() {}
	void setTexMethod(const int method) {
		textureMethod = method;
	}
	virtual int DrawObject();
	void addTex(Texture& Tex) {
		textures.push_back(Tex);
	}
	// void Set(...);

private:
	int textureMethod;  // e.g. GL_TEXTURE_2D
	vector<Texture> textures;
};
