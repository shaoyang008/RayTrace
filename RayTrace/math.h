#ifndef MATH_H
#define MATH_H

#include <vector>
#include <iostream>

using namespace std;

class vector3
{
public:
	vector3() {};
	vector3(const float &x0, const float &x1, const float &x2);
	float distance();
	vector3 operator - (const vector3& T);
	vector3 operator + (const vector3& T);
	vector3 operator * (const float& f);
	vector3 operator * (const vector3& v);
	vector3 operator - (const vector3& T) const;
	vector3 operator + (const vector3& T) const;
	vector3 operator * (const float& f) const;
	~vector3();

	static vector3 normalize(const vector3 &v);
	static vector3 cross(const vector3 &a, const vector3 &b);
	static float dot(const vector3 &a, const vector3 &b);
	friend ostream& operator<<(ostream& os, const vector3& v);

	float _vec[3];
};

class matrix4
{
public:
	matrix4() {};
	matrix4(
		const float &x0, const float &x1, const float &x2, const float &x3,
		const float &y0, const float &y1, const float &y2, const float &y3,
		const float &z0, const float &z1, const float &z2, const float &z3,
		const float &w0, const float &w1, const float &w2, const float &w3
	);
	matrix4(const float &v);
	bool inverse(matrix4& output);
	matrix4 transpose();
	vector3 transformVector(const vector3& v, float hgc);
	matrix4 operator * (const matrix4& T);
	matrix4 operator * (const float& f);
	matrix4 operator - (const matrix4& T);
	matrix4 operator + (const matrix4& T);

	friend ostream& operator<<(ostream& os, const matrix4& m);
	~matrix4();

	float _mat[4][4];
};

#endif