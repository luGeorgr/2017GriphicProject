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
	HitCube(const Point& initLeftButtom, const Point& initRightTop, const CovMatrix3& feature);
	void CalculetReal();
	void Transformation(float scalex = 1, float scaley = 1, float scalez = 1, float offsetx = 0, float offsety = 0, float offsetz = 0);
public:
	Point leftButtom, rightTop, center;
	Point realLB, realRT, realCenter;
	Point initLeftButtom, initRightTop, initCenter;
	CovMatrix3 feature; //x' = feature^-1 * x   feature 列为单位向量
};
bool HitCubeCheck(HitCube& a, HitCube& b); //两个包围盒的检测
bool HitPointCheck(HitCube& a, const float x, const float y, const float z);//包围盒与点的检测
CovMatrix3 ComputeCovMatrix3(vector<Point> points);//找出特征向量
CovMatrix3 JacobiSolver(CovMatrix3 matrix);//jacobi
void SchmidtOrthogonal(CovMatrix3& matrix);//施密特正交化
float CaculateK(float v0[3], float v1[3]);//施密特正交化求系数
void Normalize(float v[3]);//单个向量单位化
Point Transform(const Point& p, const CovMatrix3& m);//坐标转化
HitCube GenerateOBB(const vector<Point>& points);//包围盒生成
bool HitrayCheck(float x, float y, float z, HitCube& a);//射线与包围盒的检测