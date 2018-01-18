#ifndef _HIGHGUI_H_
#define _HIGHGUI_H_

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>
#include "glui.h"
#include"ParseString.h"
#include "Snapshot.h"
//#include "VideoPlayer.h"
#define INVALID 1000
using namespace std;
extern shared_ptr<View> pview;
extern shared_ptr<Model> pmodel;
int mainWindow;
float xy_aspect;
GLUI *glui1;
GLUI_Panel *panel1, *panel2, *panel3;
int obj_id = INVALID;  // 选定物体的id

GLUI_EditText *edittext_tex, *edittext_v;  // 输入纹理图片的id
string text_tex = "sky\\back.jpg";
string text_video = "Enter path here";

GLUI_EditText *edit_loadobj;
string text_loadobj = "1 1 1 0 0 0 0.1 0.1 0.1 0 0 0 car1";

GLUI_EditText *edit_attr, *edit_light, *edit_select;
string text_attr, text_light, text_select;
GLUI_EditText *edit_obj;
string text_obj = "Enter path here";
int attr_type = 0;  // 从物体的颜色、位置、缩放、旋转中选
float attr_x = 0, attr_y = 0, attr_z = 0;
int light_type = 0;  // 添加光源还是更改光源属性
float light_x = 0, light_y = 0, light_z = 0;

int item1, item2, item3, item4;
int angleX = 0, angleY = 0;
float dist = 10;
float rot[3] = { 0, 0, 0 };

#define BUTTON1 100
#define BUTTON2 101
#define BUTTON3 102
#define BUTTON4 103
#define BUTTON5 104
#define BUTTON6 105
#define BUTTON7 106
#define BUTTON8 107
#define BUTTON9 108
#define BUTTON10 109
#define BMP_HEADER_LENGTH 54
#define WIN_WID 600
#define WIN_LEN 400
#define PI1 3.14
#define MAX_DIST 20
#define MIN_DIST 2

float res[3] = { 0, 0, 0 };

class Camera {
public:
	float position[3];
	float front[3];
	float moveSpeed;
	float velocity;
	float yaw;
	float pitch;
	float dist;

	Camera(float y = -90.0, float p = 0.0, float v = 0.2f) : yaw(y), pitch(p), velocity(v), moveSpeed(0.2f), dist(1.0) {
		position[0] = position[1] = 0.0; position[2] = 5.0;
		worldUp[0] = worldUp[2] = 0.0; worldUp[1] = 1.0;
		front[0] = front[1] = front[2] = 0.0;
		updateVectors();
	}

	void updateVectors() {
		front[0] = cos(radian(yaw)) * cos(radian(pitch));
		front[1] = sin(radian(pitch));
		front[2] = sin(radian(yaw)) * cos(radian(pitch));
		normalize(front);
		float *temp1 = cross(front, worldUp);
		right[0] = temp1[0];
		right[1] = temp1[1];
		right[2] = temp1[2];
		normalize(right);
		float *temp2 = cross(right, front);
		up[0] = temp2[0];
		up[1] = temp2[1];
		up[2] = temp2[2];
		normalize(up);
	}

	float* getUpVec() {
		return up;
	}

private:
	float up[3];
	float right[3];
	float worldUp[3];

	float radian(const float rad) {
		return rad * 180.0 / PI1;
	}

	void normalize(float* vec) {
		float temp = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
		float r = sqrt(dist);
		vec[0] = vec[0] / temp * r;
		vec[1] = vec[1] / temp * r;
		vec[2] = vec[2] / temp * r;
	}

	float* cross(float* v1, float* v2) {
		res[0] = v1[1] * v2[2] - v1[2] * v2[1];
		res[1] = v1[2] * v2[0] - v1[0] * v2[2];
		res[2] = v1[0] * v2[1] - v1[1] * v2[0];
		return res;
	}
};

Camera C;

void myGlutReshape(int x, int y);
void myGlutKeyboard(unsigned char Key, int x, int y);
void myGlutMouse(int button, int button_state, int x, int y);
void myGlutMotion(int x, int y);
void callback(int control);
void myGlutMotion(int x, int y);
void myGlutMouse(int button, int button_state, int x, int y);

void texCtrlFunc(int control);
void videoFunc(int control);
void modifyObjAttrFunc(int control);
void modifyLightFunc(int control);
void objSelectFunc(int control);
void objLoadFunc(int control);

void grab(void);  // snapshot
void objOutFunc(int control);
void mainWindowRender();

void mainWindowRender()
{
	GLUI_Master.set_glutReshapeFunc(myGlutReshape);
	glutKeyboardFunc(myGlutKeyboard);
	GLUI_Master.set_glutMouseFunc(myGlutMouse);
	glutMotionFunc(myGlutMotion);
	// subwindow on the right side:
	glui1 = GLUI_Master.create_glui("Control Window", 0, 500, 200);
	panel1 = new GLUI_Rollout(glui1, "Object Params:", false);

	// ============================
	/*
	GLUI_Spinner *spinner1 = new GLUI_Spinner(panel1, "Type", &attr_type);
	spinner1->set_int_limits(0, 3);
	spinner1->set_alignment(GLUI_ALIGN_RIGHT);

	GLUI_Spinner *spinner2 = new GLUI_Spinner(panel1, "x", &attr_x);
	spinner2->set_int_limits(0.0, 10.0);
	spinner2->set_alignment(GLUI_ALIGN_RIGHT);

	GLUI_Spinner *spinner3 = new GLUI_Spinner(panel1, "y", &attr_y);
	spinner3->set_int_limits(0.0, 10.0);
	spinner3->set_alignment(GLUI_ALIGN_RIGHT);

	GLUI_Spinner *spinner4 = new GLUI_Spinner(panel1, "z", &attr_z);
	spinner4->set_int_limits(0.0, 10.0);
	spinner4->set_alignment(GLUI_ALIGN_RIGHT);
	*/
	edit_attr = new GLUI_EditText(panel1, "Attributes:", text_attr, 1, modifyObjAttrFunc);
	new GLUI_Button(panel1, "Apply", BUTTON7, modifyObjAttrFunc);
	// ============================
	edittext_tex = new GLUI_EditText(glui1, "Texture Path:", text_tex, 2, texCtrlFunc);
	// ============================
	panel2 = new GLUI_Rollout(glui1, "Lighting:", false);
	/*
	GLUI_Spinner *spinner5 = new GLUI_Spinner(panel2, "Type", &light_type);
	spinner5->set_int_limits(0, 2);
	spinner5->set_alignment(GLUI_ALIGN_RIGHT);

	GLUI_Spinner *spinner6 = new GLUI_Spinner(panel2, "x", &light_x);
	spinner6->set_int_limits(0.0, 10.0);
	spinner6->set_alignment(GLUI_ALIGN_RIGHT);

	GLUI_Spinner *spinner7 = new GLUI_Spinner(panel2, "y", &light_y);
	spinner7->set_int_limits(0.0, 10.0);
	spinner7->set_alignment(GLUI_ALIGN_RIGHT);

	GLUI_Spinner *spinner8 = new GLUI_Spinner(panel2, "z", &light_z);
	spinner8->set_int_limits(0.0, 10.0);
	spinner8->set_alignment(GLUI_ALIGN_RIGHT);
	*/
	edit_light = new GLUI_EditText(panel2, "Light params:", text_light, 3, modifyLightFunc);
	new GLUI_Button(panel2, "Apply", BUTTON8, modifyLightFunc);
	// ============================
	panel3 = new GLUI_Rollout(glui1, "Select:", false);
	//GLUI_Spinner *spinner9 = new GLUI_Spinner(panel3, "Which object", &obj_id);  // 选定物体
	//spinner9->set_int_limits(0, 15);
	//spinner9->set_alignment(GLUI_ALIGN_RIGHT);
	edit_select = new GLUI_EditText(panel3, "Select:", text_select, 4, objSelectFunc);
	// ============================
	edittext_v = new GLUI_EditText(glui1, "Video Path:", text_video, 5, videoFunc);
	edit_obj = new GLUI_EditText(glui1, "Obj Path:", text_obj, 6, objOutFunc);
	edit_loadobj = new GLUI_EditText(glui1, "load Obj:", text_loadobj, 6, objLoadFunc);
	// ============================

	new GLUI_Button(glui1, "cone", BUTTON1, callback);
	new GLUI_Button(glui1, "cyclinder", BUTTON2, callback);
	new GLUI_Button(glui1, "prism", BUTTON3, callback);
	new GLUI_Button(glui1, "sphere", BUTTON4, callback);
	new GLUI_Button(glui1, "trustum", BUTTON5, callback);
	new GLUI_Button(glui1, "Snapshot", BUTTON6, callback);
	new GLUI_Button(glui1, "Quit", 0, (GLUI_Update_CB)exit);  // quit

	glui1->set_main_gfx_window(mainWindow);
	GLUI_Translation *trans_xy = new GLUI_Translation(glui1, "XY move", GLUI_TRANSLATION_XY, C.position);
	trans_xy->set_speed(0.005);
	GLUI_Translation *trans_z = new GLUI_Translation(glui1, "Z move", GLUI_TRANSLATION_Z, &C.position[2]);

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
		case 'w': {
			C.position[1] -= C.moveSpeed;
			C.front[1] -= C.moveSpeed;
			break;
		}
		case 's': {
			C.position[1] += C.moveSpeed;
			C.front[1] += C.moveSpeed;
			break;
		}
		case 'a': {
			C.position[0] += C.moveSpeed;
			C.front[0] += C.moveSpeed;
			break;
		}
		case 'd': {
			C.position[0] -= C.moveSpeed;
			C.front[0] -= C.moveSpeed;
			break;
		}
		case 'z': {
			C.position[2] -= C.moveSpeed;
			C.front[2] -= C.moveSpeed;
			break;
		}
		case 'c': {
			C.position[2] += C.moveSpeed;
			C.front[2] += C.moveSpeed;
			break;
		}
		case 'j': {
			if (C.dist < MAX_DIST) {
				C.dist += C.moveSpeed;
				C.updateVectors();
			}
			break;
		}
		case 'l': {
			if (C.dist > MIN_DIST) {
				C.dist -= C.moveSpeed;
				C.updateVectors();
			}
			break;
		}
		case 'g': {
			if (obj_id != INVALID) {
				Params t;
				t.SetIntParams(vector<int>{obj_id, 1});
				t.SetFloatParams(vector<float>{0, 0, 3, 0.0, 0.0, 0.0, 0, 0, 3});
				pview->setObjectAttributeCommand->SetParams(t);
				pview->setObjectAttributeCommand->exec();
			}
			pmodel->ObjectMove();
			break;
		}
		case 'h': {
			if (obj_id != INVALID) {
				Params t;
				t.SetIntParams(vector<int>{obj_id, 1});
				t.SetFloatParams(vector<float>{0, 0, -3, 0.0, 0.0, 0.0, 0, 0, 3});
				pview->setObjectAttributeCommand->SetParams(t);
				pview->setObjectAttributeCommand->exec();
			}
			pmodel->ObjectMove();
			break;
		}
		case 'v': {
			if (obj_id != INVALID) {
				Params t;
				t.SetIntParams(vector<int>{obj_id, 1});
				t.SetFloatParams(vector<float>{3, 0, 0, 0.0, 0.0, 0.0, 3, 0, 0});
				pview->setObjectAttributeCommand->SetParams(t);
				pview->setObjectAttributeCommand->exec();
			}
			pmodel->ObjectMove();
			break; 
		}
		case 'b': {
			if (obj_id != INVALID) {
				Params t;
				t.SetIntParams(vector<int>{obj_id, 1});
				t.SetFloatParams(vector<float>{-3, 0, 0, 0.0, 0.0, 0.0, 3, 0, 0});
				pview->setObjectAttributeCommand->SetParams(t);
				pview->setObjectAttributeCommand->exec();
			}
			pmodel->ObjectMove();
			break;
		}
		case 'n': {
			if (obj_id != INVALID) {
				Params t;
				t.SetIntParams(vector<int>{obj_id, 1});
				t.SetFloatParams(vector<float>{0, 3, 0, 0.0, 0.0, 0.0, 0, 3, 0});
				pview->setObjectAttributeCommand->SetParams(t);
				pview->setObjectAttributeCommand->exec();
			}
			pmodel->ObjectMove();
			break;
		}
		case 'm':{
			if (obj_id != INVALID) {
				Params t;
				t.SetIntParams(vector<int>{obj_id, 1});
				t.SetFloatParams(vector<float>{0, -3, 0, 0.0, 0.0, 0.0, 0, 3, 0});
				pview->setObjectAttributeCommand->SetParams(t);
				pview->setObjectAttributeCommand->exec();
			}
			pmodel->ObjectMove();
			break;
		}
		case 'o':{
			pmodel->ObjectMove();
			break;
		}
	}
	//C.updateVectors();
	glutPostRedisplay();  // ?
}

void callback(int control)
{
	if (control == BUTTON6) {
		grab();  // snapshot
	}
}

int last_x = 0, last_y = 0;

void myGlutMotion(int x, int y)
{	
	C.yaw += (float)(x - last_x);
	C.pitch += (float)(y - last_y);
	last_x = x;
	last_y = y;
	C.updateVectors();
	glutPostRedisplay();
}

void myGlutMouse(int button, int button_state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN) {
		last_x = x;
		last_y = y;
	}
}


void texCtrlFunc(int control)  // 纹理路径文本框回车
{
	Params test;
	string content = edittext_tex->get_text();
	cout << "texture path entered. content = " << content << endl;
	vector<string> t;
	t.push_back(content);
	test.SetStringParams(t);
	test.SetIntParams(vector<int>({ 1 }));
	pview->readTexCommand->SetParams(test);
	pview->readTexCommand->exec();
}

const int bpp = 24;
int screen_w = 500, screen_h = 500;
const int pixel_w = 320, pixel_h = 180;
#if LOAD_BGRA
const int bpp = 32;
#elif LOAD_RGB24 | LOAD_BGR24
const int bpp = 24;
#elif LOAD_YUV420P
const int bpp = 12;
#endif
FILE *fp = NULL;
unsigned char buffer[pixel_w * pixel_h * bpp / 8];

void Display(void) {
	if (fread(buffer, 1, pixel_w * pixel_h * bpp / 8, fp) != pixel_w * pixel_h * bpp / 8) {
		return;
	}
	glRasterPos3f(-1.0f, 1.0f, 0);
	glPixelZoom((float)screen_w / (float)pixel_w, -(float)screen_h / (float)pixel_h);
	glDrawPixels(pixel_w, pixel_h, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	glutSwapBuffers();

}

void timeFunc(int value) {
	Display();  // Present frame every 40 ms
	glutTimerFunc(40, timeFunc, 0);
}

void videoFunc(int control)  // 视频路径文本框回车 "D://test_rgb24_320x180.rgb"
{
	string path = edittext_v->get_text();
	cout << "Video to be loaded. path: " << path << endl;
	fp = fopen(path.c_str(), "rb+");
	if (fp == NULL) {
		printf("Cannot open this file.\n");
		return;
	}
	// glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(screen_w, screen_h);
	glutCreateWindow("Simplest Video Play OpenGL");
	glutDisplayFunc(&Display);
	glutTimerFunc(40, timeFunc, 0);

	glutMainLoop();
}


void modifyObjAttrFunc(int control)
{
	string content = edit_attr->get_text();
	cout << "modifyObjAttr button pushed. content = " << content << endl;
	cout << "obj ID: ";
	for (auto i : pmodel->ObjectList)
		cout << i->getID() << "  ";
	cout << endl;
	cout << "obj ID: ";
	for (auto i : pmodel->TexList)
		cout << i->ID << "  ";
	cout << endl;
	ParseString p;
	vector<string> v = p.parse(content);
	
	float a[20];
	float f;
	int offset = 0;
	for (auto i : v) {
		std::stringstream ss;
		ss << i;
		ss >> f;
		a[offset] = f;
		offset++;
	}
	if (a[0] == 0) {
		Params t;
		t.SetIntParams(vector<int>{(int)a[1]});
		t.SetFloatParams(vector<float>{a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13]});
		pview->addObjectCommand->SetParams(t);
		pview->addObjectCommand->exec();
		if(offset>15)
			t.SetIntParams(vector<int>{(int)a[14], -1, pmodel->GetLastObject()->getID(), (int)a[15], (int)a[16]});
		else
			t.SetIntParams(vector<int>{(int)a[14], -1, pmodel->GetLastObject()->getID(), 0,0});
		pview->drawObjectCommand->SetParams(t);
		pview->drawObjectCommand->exec();
	}
	if (a[0] == 1) {
		Params t;
		t.SetIntParams(vector<int>{(int)a[1], (int)a[2]});
		t.SetFloatParams(vector<float>{a[3], a[4], a[5]});
		pview->adjustobjectCommand->SetParams(t);
		pview->adjustobjectCommand->exec();
	}

}
void modifyLightFunc(int control)
{
	cout << "obj ID: ";
	for (auto i : pmodel->LightList)
		cout << i->ID << "  ";
	cout << endl;
	string content = edit_light->get_text();
	cout << "modifyObjAttr button pushed. content = " << content << endl;
	int type;
	ParseString p;
	vector<string> v = p.parse(content);
	float t[25];
	int offset = 0;
	for (int i = 0; i < v.size(); i++) {
		stringstream ss;
		ss << v[i];
		ss >> t[offset++];
	}
	switch ((int)t[0]) {
	case 0: {  // 加一个光源
		Params p;
		p.SetIntParams(vector<int>{(int)t[0], (int)t[1]});
		vector<float> a;
		for (int i = 2; i < v.size(); i++)
			a.push_back(t[i]);
		p.SetFloatParams(a);
		pview->addOrDeleteLightCommand->SetParams(p);
		pview->addOrDeleteLightCommand->exec();
	}
	case 1: {  // 删除
		Params p;
		p.SetIntParams(vector<int>{(int)t[0], (int)t[1]});
		vector<float> a;
		for (int i = 2; i < v.size(); i++)
			a.push_back(t[i]);
		p.SetFloatParams(a);
		pview->addOrDeleteLightCommand->SetParams(p);
		pview->addOrDeleteLightCommand->exec();
	}
	case 2: {  // 颜色
		Light* l = pmodel->findLightFromID((int)t[1]).get();
		l->specular[0] = t[2];
		l->specular[1] = t[3];
		l->specular[2] = t[4];
		l->diffuse[0] = t[2];
		l->diffuse[1] = t[3];
		l->diffuse[2] = t[4];
		l->ambient[0] = t[2];
		l->ambient[1] = t[3];
		l->ambient[2] = t[4];
	}
	case 3: {  // 位置
		Light* l = pmodel->findLightFromID((int)t[1]).get();
		l->postion[0] = t[2];
		l->postion[1] = t[3];
		l->postion[2] = t[4];
	}
	}
}

void objSelectFunc(int control)
{
	cout << "obj ID: " ;
	for (auto i : pmodel->ObjectList)
		cout << i->getID() << "  ";
	cout<<endl;
	string content = edit_select->get_text();
	cout << "objSelectFunc. content = " << content << endl;
	ParseString p;
	vector<string> v = p.parse(content);

	float a[20];
	float f;
	int offset = 0;
	for (auto i : v) {
		std::stringstream ss;
		ss << i;
		ss >> f;
		a[offset] = f;
		offset++;
	}
	obj_id = (int)a[0];
	Params t;
	t.SetIntParams(vector<int>{(int)a[0], (int)a[1]});
	t.SetFloatParams(vector<float>{a[2], a[3], a[4], 0.0, 0.0, 0.0, a[2], a[3], a[4]});
	pview->setObjectAttributeCommand->SetParams(t);
	pview->setObjectAttributeCommand->exec();
}

void objOutFunc(int control)
{
	cout << "obj ID: ";
	for (auto i : pmodel->ObjectList)
		cout << i->getID() << "  ";
	cout << endl;
	string content = edit_obj->get_text();  // id
	cout << "objOutFunc. content = " << content << endl;
	ParseString p;
	vector<string> v = p.parse(content);
	stringstream ss;
	ss << v[0];
	int id;
	ss >> id;
	pmodel->GetObject(vector<int>{id})->toFile(v[1]);
}

void objLoadFunc(int control)
{
	string content = edit_loadobj->get_text();
	Params test;
	ParseString p;
	vector<string> v = p.parse(content);
	float t[25];
	int offset = 0;
	for (int i = 0; i < 12; i++) {
		stringstream ss;
		ss << v[i];
		ss >> t[offset++];
	}
	test.SetFloatParams(vector<float>{t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7], t[8], t[9], t[10], t[11]});
	test.SetIntParams(vector<int>{10});
	test.SetStringParams(vector<string>{v[12]});
	pview->addObjectCommand->SetParams(test);
	pview->addObjectCommand->exec();

	test.SetIntParams(vector<int>{pmodel->GetLastObject()->getID()});
	pview->drawobjCommand->SetParams(test);
	pview->drawobjCommand->exec();

}

#endif
