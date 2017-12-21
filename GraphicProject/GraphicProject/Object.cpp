#include"Object.h"
Object::Object()
{
	ID = count++;
}

Object::~Object()
{
}

int Object::count = 0;