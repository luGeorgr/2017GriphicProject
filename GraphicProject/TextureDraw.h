#pragma once
#include "BasicDraw.h"
#include "Texture.h"
#include "glext.h"
#include <memory>
using std::shared_ptr;

class TextureDraw : public BasicDraw {
public:
	TextureDraw() {}
	void setTexMethod(const int method = 0) {
		textureMethod = method;
	}
	virtual int DrawObject();
	void addTex(shared_ptr<Texture> Tex) {
		textures.push_back(Tex);
	}
	// void Set(...);

private:
	int textureMethod;  // e.g. GL_TEXTURE_2D
	vector<shared_ptr<Texture>> textures;
};
