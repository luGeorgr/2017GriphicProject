#include "ObjByRead.h"

int ObjByRead::setPoint() {
	ObjFile obj(this->file);
	for (int i = 0; i < obj.F.size(); i++) {
		point3.push_back(obj.V[obj.F[i].v[0]].x);
		point3.push_back(obj.V[obj.F[i].v[0]].y);
		point3.push_back(obj.V[obj.F[i].v[0]].z);
		point3.push_back(obj.V[obj.F[i].v[1]].x);
		point3.push_back(obj.V[obj.F[i].v[1]].y);
		point3.push_back(obj.V[obj.F[i].v[1]].z);
		point3.push_back(obj.V[obj.F[i].v[2]].x);
		point3.push_back(obj.V[obj.F[i].v[2]].y);
		point3.push_back(obj.V[obj.F[i].v[2]].z);
	}
	return 0;
}

int ObjByRead::setNormal() {
	ObjFile obj(this->file);
	for (int i = 0; i < obj.F.size(); i++) {
		if (obj.N.size() != 0) {
			normal3.push_back(obj.N[obj.F[i].n[0]].x);
			normal3.push_back(obj.N[obj.F[i].n[0]].y);
			normal3.push_back(obj.N[obj.F[i].n[0]].z);
			normal3.push_back(obj.N[obj.F[i].n[1]].x);
			normal3.push_back(obj.N[obj.F[i].n[1]].y);
			normal3.push_back(obj.N[obj.F[i].n[1]].z);
			normal3.push_back(obj.N[obj.F[i].n[2]].x);
			normal3.push_back(obj.N[obj.F[i].n[2]].y);
			normal3.push_back(obj.N[obj.F[i].n[2]].z);
		}
	}
	return 0;
}

int ObjByRead::setTexCoord() {
	ObjFile obj(this->file);
	for (int i = 0; i < obj.F.size(); i++) {
		if (obj.T.size() != 0) {
			texCoord3.push_back(obj.T[obj.F[i].t[0]].tu);
			texCoord3.push_back(obj.T[obj.F[i].t[0]].tv);
			texCoord3.push_back(obj.T[obj.F[i].t[1]].tu);
			texCoord3.push_back(obj.T[obj.F[i].t[1]].tv);
			texCoord3.push_back(obj.T[obj.F[i].t[2]].tu);
			texCoord3.push_back(obj.T[obj.F[i].t[2]].tv);
		}
	}
	return 0;
}
/*
int ObjByRead::setDrawMethod(int m) {
	drawMethod = m;
	return 0;
}
*/
int ObjByRead::setDrawMethod() {
	drawMethod = GL_LINE_LOOP;
	return 0;
}
