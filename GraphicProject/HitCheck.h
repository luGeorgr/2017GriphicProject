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
	CovMatrix3 feature; //x' = feature^-1 * x   feature ��Ϊ��λ����
};
bool HitCubeCheck(HitCube& a, HitCube& b); //������Χ�еļ��
bool HitPointCheck(HitCube& a, const float x, const float y, const float z);//��Χ�����ļ��
CovMatrix3 ComputeCovMatrix3(vector<Point> points);//�ҳ���������
CovMatrix3 JacobiSolver(CovMatrix3 matrix);//jacobi
void SchmidtOrthogonal(CovMatrix3& matrix);//ʩ����������
float CaculateK(float v0[3], float v1[3]);//ʩ������������ϵ��
void Normalize(float v[3]);//����������λ��
Point Transform(const Point& p, const CovMatrix3& m);//����ת��
HitCube GenerateOBB(const vector<Point>& points);//��Χ������
bool HitrayCheck(float x, float y, float z, HitCube& a);//�������Χ�еļ��