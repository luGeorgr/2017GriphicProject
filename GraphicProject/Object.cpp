#include "Object.h"

Object::Object(int type)
{
	this->type = type;
	ID = count++;
	setObjectAttribute();
}

Object::~Object()
{

}

int Object::count = 0;
void Object::toFile(string filename) {
	ofstream toOBJ;
	toOBJ.open(filename);

	for (int i = 0; i < this->point3.size(); i = i + 3) {
		ostringstream oss;
		oss << "v " << this->point3[i] << " "<<this->point3[i + 1] << " "<<this->point3[i + 2];
		toOBJ << oss.str() << endl;
	}
	for (int i = 0; i < this->normal3.size(); i = i + 3) {
		ostringstream oss;
		oss << "vn " << this->normal3[i] << " "<<this->normal3[i + 1] << " "<<this->normal3[i + 2];
		toOBJ << oss.str() << endl;
	}

	for (int i = 0; i < this->texCoord3.size(); i = i + 2) {
		ostringstream oss;
		oss << "vt " << this->texCoord3[i] << " "<<this->texCoord3[i + 1];
		toOBJ << oss.str() << endl;
	}

	for (int i = 0; i < this->point3.size(); i = i + 3) {
		ostringstream oss;
		if (i / 3 * 2 + 2 < this->texCoord3.size()) {
			oss << "f " << i << "/" << i << "/" << i << " ";
			oss << i + 1 << "/" << i + 1 << "/" << i + 1 << " ";
			oss << i + 2 << "/" << i + 2 << "/" << i + 2;
		}
		else {
			oss << "f " << i << "/" << "/" << i << " ";
			oss << i + 1 << "/" << "/" << i + 1 << " ";
			oss << i + 2 << "/" << "/" << i + 2;
		}
		toOBJ << oss.str() << endl;
	}
	toOBJ.close();



}
