#pragma once
#include <vector>
#include <string>
#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#define BITMAP_ID 0x4D42  // text whether it is bitmap file
using namespace std;



class Texture {
public:
	friend class TextureDraw;
	Texture(const string& name, const int type = 1) : 
		filename(name), texType(type) {
		ID = count++;
	}
	Texture(int type = 1) : texType(type) {}
	void bindTex(const int h = 0, const int w = 0, void* array = NULL);
	int ID;

protected:
	GLuint texture;
	const string filename;
	const int texType;  // 0, 1, 2, 3

private:
	static int count;
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
