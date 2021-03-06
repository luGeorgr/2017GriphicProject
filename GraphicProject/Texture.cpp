#include "Texture.h"
int Texture::count = 0;
unsigned char * Texture::loadImageFile(BITMAPINFOHEADER *bitmapInfoHeader)
{
	img.Load(filename.c_str());
	bitmapInfoHeader->biBitCount = img.GetBPP();
	bitmapInfoHeader->biHeight = img.GetHeight();
	bitmapInfoHeader->biWidth = img.GetWidth();
	if (img.GetPitch()<0) //GetBits的作用就是获得纹理的位信息缓冲区指针，如果位图是从下到上， 则指向缓冲区末端，否则指向缓冲区首端。而img.GetPitch 就是起这个判断作用，小于 0 指向末端
		return (unsigned char *)img.GetBits() + (img.GetPitch()*(img.GetHeight() - 1));
	else
		return (unsigned char *)img.GetBits();
}
unsigned char* Texture::load2DBmpFile(BITMAPINFOHEADER *bitmapInfoHeader)//no use
{
	FILE *filePtr;
	BITMAPFILEHEADER bitmapFileHeader;	// bitmap file header
	unsigned char *bitmapImage;  // bitmap data
	int	imageIdx = 0;  // image position index
	unsigned char tempRGB;	// swap

	filePtr = fopen(filename.c_str(), "rb");
	if (filePtr == NULL)
		return NULL;
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// check bitmap
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}

	// get bitmap header
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];  // create buffer
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);  // read
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {  // swap
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	fclose(filePtr);
	return bitmapImage;
}

void Texture::load2DBmpTex()
{
	BITMAPINFOHEADER bitmapInfoHeader;
	unsigned char* bitmapData;  // texture data
	bitmapData = loadImageFile(&bitmapInfoHeader);  // call function above =====
	if (texType == 1) {
		glBindTexture(GL_TEXTURE_2D, texture);
		// 指定当前纹理的放大/缩小过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		if(bitmapInfoHeader.biBitCount==32)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmapInfoHeader.biWidth, 
				bitmapInfoHeader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmapData);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
				bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
	}
	else if (texType == 0) {
		glBindTexture(GL_TEXTURE_1D, texture);
		// 指定当前纹理的放大/缩小过滤方式
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		// ===== whether it has "bitmapInfoHeader.biWidth"
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, bitmapInfoHeader.biWidth, 0, 
			GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
	}
}

void Texture::bindTex(const int h, const int w, void* array)
{
	glGenTextures(1, &texture);
	if (texType == 1)
		load2DBmpTex();
	else if (texType == 3) {  // selfdef2d
		// genTexBoard();
		glBindTexture(GL_TEXTURE_2D, texture);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, h, w, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLubyte**)array);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else if (texType == 2) {  // 一维图像宽度必须为2的幂 =====
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_1D, texture);
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLubyte*)array);  // h should be width
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}
