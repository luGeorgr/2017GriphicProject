#include "HitCheck.h"

bool HitCubeCheck(HitCube & a, HitCube & b)
{
	bool flag = false;
	a.feature.getTransportMatrix();
	Point b2al = Transform(Transform(b.leftButtom, b.feature), a.feature);
	Point b2ar = Transform(Transform(b.rightTop, b.feature), a.feature);
	a.feature.getTransportMatrix();
	b.feature.getTransportMatrix();
	Point a2bl = Transform(Transform(a.leftButtom, a.feature), b.feature);
	Point a2br = Transform(Transform(a.rightTop, b.feature), b.feature);
	b.feature.getTransportMatrix();

	if (((b2al.x >= a.leftButtom.x && b2al.x <= a.rightTop.x) || (a.leftButtom.x >= b2al.x && a.leftButtom.x <= b2ar.x)) &&
		((b2al.y >= a.leftButtom.y && b2al.y <= a.rightTop.y) || (a.leftButtom.y >= b2al.y && a.leftButtom.y <= b2ar.y)) &&
		((b2al.z >= a.leftButtom.z && b2al.z <= a.rightTop.z) || (a.leftButtom.z >= b2al.z && a.leftButtom.z <= b2ar.z)) &&
		((a2bl.x >= b.leftButtom.x && a2bl.x <= b.rightTop.x) || (b.leftButtom.x >= a2bl.x && b.leftButtom.x <= a2br.x)) &&
		((a2bl.y >= b.leftButtom.y && a2bl.y <= b.rightTop.y) || (b.leftButtom.y >= a2bl.y && b.leftButtom.y <= a2br.y)) &&
		((a2bl.z >= b.leftButtom.z && a2bl.z <= b.rightTop.z) || (b.leftButtom.z >= a2bl.z && b.leftButtom.z <= a2br.z)))
		flag = true;
	return flag;

}

bool HitPointCheck(HitCube & a, const float x, const float y, const float z)
{
	bool flag = false;
	a.feature.getTransportMatrix();
	Point temp = Transform(Point(x, y, z), a.feature);
	if ((temp.x <= a.rightTop.x && temp.x >= a.leftButtom.x) &&
		(temp.y <= a.rightTop.y && temp.y >= a.leftButtom.y) &&
		(temp.z <= a.rightTop.z && temp.z >= a.leftButtom.z))
		flag = true;
	a.feature.getTransportMatrix();
	return flag;
}

CovMatrix3 ComputeCovMatrix3(vector<Point> points)
{
	float avg_x = 0.0, avg_y = 0.0, avg_z = 0.0;
	CovMatrix3 result;
	int size = points.size();
	for (int i = 0; i < size; i++) {
		avg_x += points[i].x;
		avg_y += points[i].y;
		avg_z += points[i].z;
	}
	avg_x /= size; avg_y /= size; avg_z /= size;
	for (int i = 0; i < size; i++) {
		points[i].x = points[i].x - avg_x;
		points[i].y = points[i].y - avg_y;
		points[i].z = points[i].z - avg_z;
	}
	float data[3];
	for (int row = 0; row < 3; row++) {

		for (int col = row; col < 3; col++) {

			float covData = 0.0;
			for (int i = 0; i < size; i++) {
				data[0] = points[i].x;
				data[1] = points[i].y;
				data[2] = points[i].z;
				covData += data[row] * data[col];
			}
			covData /= size;
			result.setValue(covData, row, col);
			result.setValue(covData, col, row);
		}
	}
	return result;
}

CovMatrix3 JacobiSolver(CovMatrix3 matrix)
{
	static const int totalCount = 50;
	static const float eps = 0.0001;
	CovMatrix3 result;
	//init result
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j)
				result.setValue(1.0, i, j);
			else result.setValue(0, i, j);
		}
	}
	int nCount = 0;
	while (1) 
	{
		//find maximal number
		float max = abs(matrix.getValue(0, 1));
		int row = 0, col = 1;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (i != j && abs(matrix.getValue(i, j)) > max) {
					max = matrix.getValue(i, j);
					row = i;
					col = j;
				}
			}
		}
		if (max < eps)
			break;
		if (nCount > totalCount)
			break;
		nCount += 1;
		float pp = matrix.getValue(row, row);
		float pq = matrix.getValue(row, col);
		float qq = matrix.getValue(col, col);

		float theta = 0.5 * atan(-2 * pq /( qq - pp));
		float sinTheta = sin(theta);
		float cosTheta = cos(theta);
		float sin2Theta = sin(2 * theta);
		float cos2Theta = cos(2 * theta);

		matrix.setValue(pp * cosTheta * cosTheta + qq * sinTheta * sinTheta + 2 * pq * cosTheta * sinTheta, row, row);
		matrix.setValue(pp * sinTheta * sinTheta + qq * cosTheta * cosTheta - 2 * pq * cosTheta * sinTheta, col, col);
		matrix.setValue(0.5 * (qq - pp) * sin2Theta + pq * cos2Theta, row, col);
		matrix.setValue(0.5 * (qq - pp) * sin2Theta + pq * cos2Theta, col, row);

		for (int i = 0; i < 3; i++) {
			if (i != row && i != col) {
				float pi = matrix.getValue(row, i);
				float qi = matrix.getValue(col, i);
				matrix.setValue(pi * cosTheta + sinTheta * qi, row, i);
				matrix.setValue(-pi * sinTheta + cosTheta * qi, col, i);
			}
		}

		for (int i = 0; i < 3; i++) {
			if (i != row && i != col) {
				float ip = matrix.getValue(i, row);
				float iq = matrix.getValue(i, col);
				matrix.setValue(ip * cosTheta + sinTheta * iq, i, row);
				matrix.setValue(-ip * sinTheta + cosTheta * iq, i, col);
			}
		}

		//计算特征向量
		for (int i = 0; i < 3; i++) {
			float pi = result.getValue(i, row);
			float qi = result.getValue(i, col);
			result.setValue(cosTheta * pi + sinTheta * qi, i, row);
			result.setValue(-sinTheta * pi + cosTheta * qi, i, col);
		}
	}
	return result;
}

void SchmidtOrthogonal(CovMatrix3 & matrix)
{
	float v0[3], v1[3], v2[3];

	for (int i = 0; i < 3; i++) {
		v0[i] = matrix.getValue(i, 0);
	}
	for (int i = 0; i < 3; i++)
		v1[i] = matrix.getValue(i, 1);
	for (int i = 0; i < 3; i++)
		v2[i] = matrix.getValue(i, 2);

	float k = CaculateK(v0, v1);
	for (int i = 0; i < 3; i++) {
		v1[i] = v1[i] - k * v0[i];
	}

	k = CaculateK(v0, v2);
	float k1 = CaculateK(v1, v2);
	for (int i = 0; i < 3; i++) {
		v2[i] = v2[i] - k * v0[i] - k1 * v1[i];
	}

	Normalize(v0);
	Normalize(v1);
	Normalize(v2);
	for(int i = 0; i < 3; i++)
		matrix.setValue(v0[i], i, 0);
	for (int i = 0; i < 3; i++)
		matrix.setValue(v1[i], i, 1);
	for (int i = 0; i < 3; i++)
		matrix.setValue(v2[i], i, 2);
}

float CaculateK(float v0[3], float v1[3])
{
	float sum1 = 0, sum2 = 0;
	for (int i = 0; i < 3; i++) {
		sum1 += v0[i] * v1[i];
		sum2 += v0[i] * v0[i];
	}
	float k = sum1 / sum2;
	return k;
}

void Normalize(float v[3])
{
	float sum = 0;
	for (int i = 0; i < 3; i++)
		sum += v[i] * v[i];
	sum = sqrt(sum);
	for (int i = 0; i < 3; i++)
		v[i] = v[i] / sum;
}

Point Transform(const Point & p, const CovMatrix3 & m)
{
	float x, y, z;
	x = m.getValue(0, 0) * p.x + m.getValue(0, 1) * p.y + m.getValue(0, 2) * p.z;
	y = m.getValue(1, 0) * p.x + m.getValue(1, 1) * p.y + m.getValue(1, 2) * p.z;
	z = m.getValue(2, 0) * p.x + m.getValue(2, 1) * p.y + m.getValue(2, 2) * p.z;
	return Point(x, y, z);
}

HitCube GenerateOBB(const vector<Point>& points)
{
	float xMin = 0, xMax = 0, yMin = 0, yMax = 0, zMin = 0, zMax = 0;
	CovMatrix3 matrix = ComputeCovMatrix3(points);
	CovMatrix3 featureMatrix = JacobiSolver(matrix);
	SchmidtOrthogonal(featureMatrix);
	featureMatrix.getTransportMatrix();
	//caculate center point
	vector<Point> v;
	for (int i = 0; i < points.size(); i++) {
		v.push_back(Transform(points[i], featureMatrix));
	}

	for (int i = 0; i < v.size(); i++) 
	{
		if (xMax < v[i].x)
			xMax = v[i].x;
		if (xMin > v[i].x)
			xMin = v[i].x;
		if (yMax < v[i].y)
			yMax = v[i].y;
		if (yMin > v[i].y)
			yMin = v[i].y;
		if (zMax < v[i].z)
			zMax = v[i].z;
		if (zMin > v[i].z)
			zMin = v[i].z;
	}
	float deltaX = (xMax - xMin) / 2;
	float deltaY = (yMax - yMin) / 2;
	float deltaZ = (zMax - zMin) / 2;
	float centerx = (xMax + xMin) / 2, centery = (yMax + yMin) / 2, centerz = (zMax + zMin) / 2;
	featureMatrix.getTransportMatrix();
	return HitCube(Point(centerx - deltaX, centery - deltaY, centerz - deltaZ), Point(centerx + deltaX, centery + deltaY, centerz + deltaZ), featureMatrix);
}

bool HitrayCheck(float x, float y, float z, HitCube & a)
{
	CovMatrix3 feature;
	float x1 = 1, y1 = 1, z1 = (x + y) / (-z);
	float x2 = y * z1 - z * y1, y2 = z * x1 - x * z1, z2 = x * y1 - y * x1;
	feature.setValue(x, 0, 0); feature.setValue(x1, 0, 1); feature.setValue(x2, 0, 2);
	feature.setValue(y, 1, 0); feature.setValue(y1, 1, 1); feature.setValue(y2, 1, 2);
	feature.setValue(z, 2, 0); feature.setValue(z1, 2, 1); feature.setValue(z2, 2, 2);
	SchmidtOrthogonal(feature);
	HitCube newCube = HitCube(Point(-1000000.0,-0.1,-0.1), Point(1000000.0,0.1,0.1), feature);
	return HitCubeCheck(newCube, a);
}

HitCube::HitCube(const Point& initLeftButtom, const Point& initRightTop, const CovMatrix3& feature)
	:initLeftButtom(initLeftButtom), initRightTop(initRightTop), feature(feature)
{
	initCenter.x = (initLeftButtom.x + initRightTop.x) / 2;
	initCenter.y = (initLeftButtom.y + initRightTop.y) / 2;
	initCenter.z = (initLeftButtom.z + initRightTop.z) / 2;
	CalculetReal();
	Transformation(1, 1, 1, 0, 0, 0);
}

void HitCube::CalculetReal()
{
	realLB = Transform(initLeftButtom, feature);
	realRT = Transform(initRightTop, feature);
	realCenter = Transform(initCenter, feature);
}


void HitCube::Transformation(float scalex, float scaley, float scalez, float offsetx, float offsety, float offsetz)
{
	CalculetReal();
	realLB.x -= realCenter.x; realLB.x *= scalex; realLB.x += realCenter.x + offsetx;
	realLB.y -= realCenter.y; realLB.y *= scaley; realLB.y += realCenter.y + offsety;
	realLB.z -= realCenter.z; realLB.z *= scalez; realLB.z += realCenter.z + offsetz;
	realRT.x -= realCenter.x; realRT.x *= scalex; realRT.x += realCenter.x + offsetx;
	realRT.y -= realCenter.y; realRT.y *= scaley; realRT.y += realCenter.y + offsety;
	realRT.z -= realCenter.z; realRT.z *= scalez; realRT.z += realCenter.z + offsetz;
	realCenter.x += offsetx; realCenter.y += offsety; realCenter.z += offsetz;
	feature.getTransportMatrix();
	this->leftButtom = Transform(realLB, feature);
	this->rightTop = Transform(realRT, feature);
	this->center = Transform(realCenter, feature);
	feature.getTransportMatrix();
}

