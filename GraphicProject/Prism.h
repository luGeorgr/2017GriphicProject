#include"Object.h"
#define PI 3.14159265358979323846
class Prism :public Object
{
public:
	void GeneratorHitCube() {

		vector<Point> pv;
		for (int i = 0; i < point3.size(); i += 3)
		{
			pv.push_back(Point(point3[i], point3[i + 1], point3[i + 2]));
		}
		this->hitCubes.push_back(GenerateOBB(pv));
	}
	Prism(int numOfFace, float raduis, float height) :Object(4), numOfFace(numOfFace), radius(raduis), height(height)
	{
		setPoint();
		setNormal();
		setTexCoord();
		setDrawMethod();
		GeneratorHitCube();
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
