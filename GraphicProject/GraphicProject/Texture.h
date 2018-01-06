#pragma once
#include <vector>
#include <string>
#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#define BITMAP_ID 0x4D42  // text whether it is bitmap file
using namespace std;

enum TEX_TYPE { normal1d, normal2d, selfdef1d, selfdef2d };

class Texture {
public:
	friend class TextureDraw;
	Texture(string& name, enum TEX_TYPE type = normal2d) : 
		filename(name), texType(type) {}
	void bindTex(void* array, const int h, const int w);

protected:
	GLuint texture;
	const string filename;
	const enum TEX_TYPE texType;

private:
	unsigned char *load2DBmpFile(BITMAPINFOHEADER *bitmapInfoHeader);
	void load2DBmpTex();

	static GLubyte board[32][32][3];  // 自定义棋盘格纹理
	static void genTexBoard() {
		for (int i = 0; i < 32; i++) {
			for (int j = 0; j < 32; j++) {
				board[i][j][0] = (((i & 0x04) ^ (j & 0x04)) == 0) ? GLubyte(255) : 0;
				board[i][j][1] = 0;
				board[i][j][2] = 0;
			}
		}
	}

	static GLubyte line[4][3];
	static void genTexLine() {
		line[0][0] = 32;
		line[1][0] = 64;
		line[2][0] = 128;
		line[3][0] = 255;
		for (int i = 0; i < 4; i++)
			line[i][1] = line[i][2] = 0;
	}
};
