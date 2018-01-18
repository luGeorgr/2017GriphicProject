#include"ObjByRead.h"


int ObjByRead::setPoint() {
	for (int i = 0; i < obj->F.size(); i++) {
		
			for (int j = 0; j < obj->F[i].type; j++) {
				point3.push_back(obj->V[obj->F[i].v[j]].x);
				point3.push_back(obj->V[obj->F[i].v[j]].z);
				point3.push_back(obj->V[obj->F[i].v[j]].y);
			}
	}
	return 0;
}

int ObjByRead::setNormal() {
	for (int i = 0; i < obj->F.size(); i++) {
		if (obj->N.size() != 0) {
			for (int j = 0; j < obj->F[i].type; j++) {
				normal3.push_back(obj->N[obj->F[i].n[j]].x);
				normal3.push_back(obj->N[obj->F[i].n[j]].z);
				normal3.push_back(obj->N[obj->F[i].n[j]].y);
			}


		}
	}
	return 0;
}

int ObjByRead::setTexCoord() {
	for (int i = 0; i < obj->F.size(); i++) {
		if (obj->T.size() != 0) {
			for (int j = 0; j < obj->F[i].type; j++) {
				texCoord3.push_back(obj->T[obj->F[i].t[j]].tu);
				texCoord3.push_back(obj->T[obj->F[i].t[j]].tv);
			}
		}
	}
	return 0;
}

int ObjByRead::setMaterial() {
	
	for (int i = 0; i < obj->F.size(); i++) {
		if (obj->M.size() != 0) {
			material.push_back(obj->M[obj->F[i].m_index]);
		}
	}
	return 0;
}

int ObjByRead::setIndex()
{
	for (int i = 0; i < obj->F.size(); i++) {
		index.push_back(obj->F[i].m_index);
	}
	return 0;
}

int ObjByRead::setTex()
{
	for (int i = 0; i < obj->M.size(); i++) {
		Material* m = &obj->M[i];
		if (m->map_Kd != "")
		{
			shared_ptr<Texture>t = shared_ptr<Texture>(new Texture(m->map_Kd, i, 1));
			t->bindTex();
			KdTexList.push_back(t);
			t->setKa(m->Ka);
			t->setKs(m->Ks);
			t->setKe(m->Ke);
			t->setKd(m->Kd);
		}
		else
		{
			shared_ptr<Texture>t = shared_ptr<Texture>(new Texture("", -1, 1));
			KdTexList.push_back(t);
			t->setKa(m->Ka);
			t->setKs(m->Ks);
			t->setKe(m->Ke);
			t->setKd(m->Kd);
		}
		if (m->map_Ka != "")
		{
			shared_ptr<Texture>t = shared_ptr<Texture>(new Texture(m->map_Ka, i, 1));
			t->bindTex();
			KaTexList.push_back(t);
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
	drawMethod = GL_TRIANGLES;
	return 0;
}

int ObjByRead::setFace(){
	for (int i = 0; i < obj->F.size(); i++) {
		if (obj->T.size() != 0) {
			face.push_back(obj->F[i].type);
		}
	}
	return 0;
}




