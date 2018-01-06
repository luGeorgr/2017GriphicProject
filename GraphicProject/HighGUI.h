#ifndef _HIGHGUI_H_
#define _HIGHGUI_H_

#include <Windows.h>
#include <stdio.h>
#include "glui.h"

int mainWindow;
float xy_aspect;
GLUI *glui1, *glui2;
GLUI_Panel *panel1;
int spin1_value = 10;
float spin2_value = 2.0;
int item1, item2, item3, item4;
int last_x = 0, last_y = 0;
#define BUTTON1 100
#define BUTTON2 101
#define BUTTON3 102
#define BUTTON4 103
#define BMP_HEADER_LENGTH 54
#define WIN_WID 600
#define WIN_LEN 400
void myGlutReshape(int x, int y);
void myGlutKeyboard(unsigned char Key, int x, int y);
void myGlutMouse(int button, int button_state, int x, int y);
void myGlutMotion(int x, int y);
void callback(int control);
void myGlutMotion(int x, int y);
void myGlutMouse(int button, int button_state, int x, int y);
void grab(void);  // snapshot
void mainWindowRender();

float eye[] = { 5, 0, 5 };
float center[] = { 0, 0, 0 };

void mainWindowRender()
{
	GLUI_Master.set_glutReshapeFunc(myGlutReshape);
	GLUI_Master.set_glutKeyboardFunc(myGlutKeyboard);
	GLUI_Master.set_glutMouseFunc(myGlutMouse);
	glutMotionFunc(myGlutMotion);
	// subwindow on the right side:
	glui1 = GLUI_Master.create_glui_subwindow(mainWindow, GLUI_SUBWINDOW_RIGHT);
	panel1 = new GLUI_Rollout(glui1, "Panel Area", false);

	GLUI_Spinner *spinner1 = new GLUI_Spinner(panel1, "Segments:", &spin1_value);
	spinner1->set_int_limits(0, 100);
	spinner1->set_alignment(GLUI_ALIGN_RIGHT);

	GLUI_Spinner *spinner2 = new GLUI_Spinner(panel1, "Scale:", &spin2_value);
	spinner2->set_float_limits(0.1, 5.0);
	spinner2->set_alignment(GLUI_ALIGN_RIGHT);

	GLUI_Rollout *options = new GLUI_Rollout(glui1, "Options", true);
	new GLUI_Checkbox(options, "Draw sphere", &item1);
	new GLUI_Checkbox(options, "Draw torus", &item2);
	new GLUI_Checkbox(options, "Draw axes", &item3);
	new GLUI_Checkbox(options, "Draw text", &item4);

	new GLUI_Button(glui1, "move1", BUTTON1, callback);
	new GLUI_Button(glui1, "move2", BUTTON2, callback);
	new GLUI_Button(glui1, "move3", BUTTON3, callback);
	new GLUI_Button(glui1, "Snapshot", BUTTON4, callback);
	new GLUI_Button(glui1, "Quit", 0, (GLUI_Update_CB)exit);  // quit

	glui1->set_main_gfx_window(mainWindow);
	GLUI_Translation *trans_xy = new GLUI_Translation(glui1, "XY move", GLUI_TRANSLATION_XY, eye);
	trans_xy->set_speed(0.005);
	GLUI_Translation *trans_z = new GLUI_Translation(glui1, "Z move", GLUI_TRANSLATION_Z, &eye[2]);

	glutMotionFunc(myGlutMotion);
	glutMouseFunc(myGlutMouse);
}

void myGlutReshape(int x, int y)
{
	int tx, ty, tw, th;
	GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
	glViewport(tx, ty, tw, th);
	xy_aspect = (float)tw / (float)th;
	glutPostRedisplay();
}

void myGlutKeyboard(unsigned char Key, int x, int y)
{
	switch (Key) {
	case 27:
	case 'q': exit(0); break;
	};
	glutPostRedisplay();  // ?
}

void callback(int control)
{
	if (control == BUTTON4) {
		GLUI_FileBrowser *browser = new GLUI_FileBrowser(glui1, "save", 1);
		grab();  // snapshot
	}
}

void myGlutMotion(int x, int y)
{
	center[2] += (float)(y - last_y) / 10.0;
	center[1] -= (float)(x - last_x) / 10.0;
	// printf("x: %d, y: %d, last_x: %d, last_y: %d\n", x, y, last_x, last_y);
	last_x = x;
	last_y = y;
	glutPostRedisplay();
}

void myGlutMouse(int button, int button_state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN) {
		last_x = x;
		last_y = y;
	}
}

void grab(void)
{
	FILE* pDummyFile;
	FILE* pWritingFile;
	GLubyte* pPixelData;
	GLubyte BMP_Header[BMP_HEADER_LENGTH];
	GLint i, j;
	GLint PixelDataLength;

	i = WIN_WID * 3;
	while (i % 4 != 0) ++i;
	PixelDataLength = i * WIN_LEN;

	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if (pPixelData == 0)
		exit(0);
	pDummyFile = fopen("bitmap1.bmp", "rb");
	if (pDummyFile == 0)
		exit(0);
	printf("fopen\n");
	pWritingFile = fopen("D://grab.bmp", "wb");
	if (pWritingFile == 0)
		exit(0);

	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);
	i = WIN_WID;
	j = WIN_LEN;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, WIN_WID, WIN_LEN, GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
}

#endif
