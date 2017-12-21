#include"Object.h"
Object::Object(int type)
{
	this->type = type;
	ID = count++;
}

Object::~Object()
{
}

int Object::count = 0;