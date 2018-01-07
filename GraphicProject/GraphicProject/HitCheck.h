#pragma once
#include<vector>
using std::vector;
class Point {
public:
	
	Point(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
	float x, y, z;
};

class CovMatrix3 {
public:
	CovMatrix3() {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				matrix[i][j] = 0;
	}
	void setValue(float value, int row, int col)
	{ 
		matrix[row][col] = value; 
	}

	float getValue(int row, int col) const
	{
		return matrix[row][col];
	}
	void getTransportMatrix() {
		float temp[3][3];
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				temp[i][j] = matrix[j][i];
			}
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				matrix[i][j] = temp[i][j];
			}
		}
	}
private:
	float matrix[3][3];
};
class HitCube {
public:
	HitCube(Point leftButtom, Point rightTop, CovMatrix3 feature)
		:leftButtom(leftButtom), rightTop(rightTop), feature(feature)
	{}
public:
	Point leftButtom, rightTop;
	CovMatrix3 feature; //x' = feature^-1 * x
};
bool HitCubeCheck(HitCube& a, HitCube& b);
bool HitPointCheck(HitCube& a, const float x, const float y, const float z);
CovMatrix3 ComputeCovMatrix3(vector<Point> points);
CovMatrix3 JacobiSolver(CovMatrix3 matrix);
void SchmidtOrthogonal(CovMatrix3& matrix);
float CaculateK(float v0[3], float v1[3]);
void Normalize(float v[3]);
Point Transform(const Point& p, const CovMatrix3& m);
HitCube GenerateOBB(const vector<Point>& points);