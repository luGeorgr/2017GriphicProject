#include"Object.h"
#define PI 3.14159265358979323846
class Prism :public Object
{
public:
	Prism(int numOfFace, float raduis, float height) :Object(0), numOfFace(numOfFace), radius(raduis), height(height)
	{
		setPoint();
		setNormal();
		setTexCoord();
		setDrawMethod();
	}
private:
	int setPoint();
	int setNormal();
	int setTexCoord();
	int setDrawMethod();
	int numOfFace;
	float radius;
	float height;
};
