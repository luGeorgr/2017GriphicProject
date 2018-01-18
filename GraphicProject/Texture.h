#pragma once
#include <vector>
#include <string>
#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <atlimage.h>
#define BITMAP_ID 0x4D42  // text whether it is bitmap file
using namespace std;


class SkyDraw;
class Texture {
public:
	friend class TextureDraw;
	friend class ObjDraw;
	Texture(const string& name, const int type = 1) : 
		filename(name), texType(type) {
		ID = count++;
	}
	Texture(const string& name,int id,const int type) ://自定义ID，只用于obj，ID = -1为空texture
		filename(name), texType(type) {
		ID = id;
	}
	Texture(int type = 1) : texType(type) { ID = count++; }
	void bindTex(const int h = 0, const int w = 0, void* array = NULL);
	int ID;
	void setKa(float a[]) { Ka[0] = a[0]; Ka[1] = a[1]; Ka[2] = a[2]; }
	void setKd(float d[]) { Kd[0] = d[0]; Kd[1] = d[1]; Kd[2] = d[2]; }
	void setKs(float s[]) { Ks[0] = s[0]; Ks[1] = s[1]; Ks[2] = s[2]; }
	void setKe(float e[]) { Ke[0] = e[0]; Ke[1] = e[1]; Ke[2] = e[2]; }
protected:
	friend class SkyDraw;
	GLuint texture;
	const string filename;
	const int texType;  // 0, 1, 2, 3
	float Ka[3];
	float Ks[3];
	float Kd[3];
	float Ke[3];
private:
	static int count;
	CImage img;
	unsigned char *loadImageFile(BITMAPINFOHEADER *bitmapInfoHeader);
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
