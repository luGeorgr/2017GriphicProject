#include"Sphere.h"

int Sphere::setPoint()
{
	double ustep = 1 / (double)uStepsNum, vstep = 1 / (double)vStepNum;
	double u = 0, v = 0;
	//绘制上端三角形组
	for (int i = 0; i<uStepsNum; i++)
	{
		Point a = calPoint(0, 0);
		Point b = calPoint(u, vstep);
		Point c = calPoint(u + ustep, vstep);
		point3.push_back(a.x);
		point3.push_back(a.y);
		point3.push_back(a.z);
		normal3.push_back(a.normalx);
		normal3.push_back(a.normaly);
		normal3.push_back(a.normalz);
		point3.push_back(b.x);
		point3.push_back(b.y);
		point3.push_back(b.z);
		normal3.push_back(b.normalx);
		normal3.push_back(b.normaly);
		normal3.push_back(b.normalz);
		point3.push_back(c.x);
		point3.push_back(c.y);
		point3.push_back(c.z);
		normal3.push_back(c.normalx);
		normal3.push_back(c.normaly);
		normal3.push_back(c.normalz);
		u += ustep;
	}
	//绘制中间四边形组
	u = 0, v = vstep;
	for (int i = 1; i<vStepNum - 1; i++)
	{
		for (int j = 0; j<uStepsNum; j++)
		{
			Point a = calPoint(u, v);
			Point b = calPoint(u + ustep, v);
			Point c = calPoint(u + ustep, v + vstep);
			Point d = calPoint(u, v + vstep);

			point3.push_back(a.x);
			point3.push_back(a.y);
			point3.push_back(a.z);
			normal3.push_back(a.normalx);
			normal3.push_back(a.normaly);
			normal3.push_back(a.normalz);
			point3.push_back(b.x);
			point3.push_back(b.y);
			point3.push_back(b.z);
			normal3.push_back(b.normalx);
			normal3.push_back(b.normaly);
			normal3.push_back(b.normalz);
			point3.push_back(c.x);
			point3.push_back(c.y);
			point3.push_back(c.z);
			normal3.push_back(c.normalx);
			normal3.push_back(c.normaly);
			normal3.push_back(c.normalz);

			point3.push_back(c.x);
			point3.push_back(c.y);
			point3.push_back(c.z);
			normal3.push_back(c.normalx);
			normal3.push_back(c.normaly);
			normal3.push_back(c.normalz);
			point3.push_back(d.x);
			point3.push_back(d.y);
			point3.push_back(d.z);
			normal3.push_back(d.normalx);
			normal3.push_back(d.normaly);
			normal3.push_back(d.normalz);
			point3.push_back(a.x);
			point3.push_back(a.y);
			point3.push_back(a.z);
			normal3.push_back(a.normalx);
			normal3.push_back(a.normaly);
			normal3.push_back(a.normalz);

			u += ustep;
		}
		v += vstep;
	}
	//绘制下端三角形组
	u = 0;
	for (int i = 0; i<uStepsNum; i++)
	{
		glBegin(GL_LINE_LOOP);
		Point a = calPoint(0, 1);
		Point b = calPoint(u, 1 - vstep);
		Point c = calPoint(u + ustep, 1 - vstep);
		point3.push_back(a.x);
		point3.push_back(a.y);
		point3.push_back(a.z);
		normal3.push_back(a.normalx);
		normal3.push_back(a.normaly);
		normal3.push_back(a.normalz);
		point3.push_back(b.x);
		point3.push_back(b.y);
		point3.push_back(b.z);
		normal3.push_back(b.normalx);
		normal3.push_back(b.normaly);
		normal3.push_back(b.normalz);
		point3.push_back(c.x);
		point3.push_back(c.y);
		point3.push_back(c.z);
		normal3.push_back(c.normalx);
		normal3.push_back(c.normaly);
		normal3.push_back(c.normalz);
		glEnd();
	}
	return 0;
}

int Sphere::setNormal()
{
	//caculate last function
	return 0;
}

int Sphere::setTexCoord()
{
	for (int i = 0; i < point3.size(); i += 3) {
		float x = point3[i], y = point3[i + 1], z = point3[i + 2];
		float v = asin(z / radius) / PI + 0.5;
		float u = atan(y / x) / 2 / PI;
		texCoord3.push_back(v);
		texCoord3.push_back(u);
	}
	return 0;
}

int Sphere::setDrawMethod()
{
	drawMethod = GL_TRIANGLES;
	return 0;
}
