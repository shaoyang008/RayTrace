#include "Transform.h"

matrix4 Transform::rotate(const float degrees, const vector3& axis) 
{
	double c = cos(degrees * pi / 180.0), s = sin(degrees * pi / 180.0);
	vector3 an = vector3::normalize(axis);
	matrix4 I(1.0), C(c), S(s);

	matrix4 R_2(
		an._vec[0] * an._vec[0], an._vec[0] * an._vec[1], an._vec[0] * an._vec[2], 0,
		an._vec[0] * an._vec[1], an._vec[1] * an._vec[1], an._vec[2] * an._vec[1], 0,
		an._vec[0] * an._vec[2], an._vec[2] * an._vec[1], an._vec[2] * an._vec[2], 0,
		0, 0, 0, 1
	);
	matrix4 R_3(
		0, -an._vec[2], an._vec[1], 0,
		an._vec[2], 0, -an._vec[0], 0,
		-an._vec[1], an._vec[0], 0, 0,
		0, 0, 0, 1
	);
	matrix4 ans = (C * I + (I - C) * R_2 + S * R_3);
	ans._mat[0][3] = 0;
	ans._mat[1][3] = 0;
	ans._mat[2][3] = 0;
	ans._mat[3][3] = 1;
	ans._mat[3][2] = 0;
	ans._mat[3][1] = 0;
	ans._mat[3][0] = 0;
	return ans;
}

matrix4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    matrix4 ret(sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
    return ret;
}

matrix4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    matrix4 ret(1, 0, 0, tx, 0, 1, 0, ty, 0, 0, 1, tz, 0, 0, 0, 1);
    return ret;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
