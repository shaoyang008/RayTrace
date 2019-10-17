#include "math.h"
#include <iostream>
#include <math.h>

matrix4::matrix4(
	const float &x0, const float &x1, const float &x2, const float &x3,
	const float &y0, const float &y1, const float &y2, const float &y3,
	const float &z0, const float &z1, const float &z2, const float &z3,
	const float &w0, const float &w1, const float &w2, const float &w3)
{
	_mat[0][0] = x0;
	_mat[0][1] = x1;
	_mat[0][2] = x2;
	_mat[0][3] = x3;
	_mat[1][0] = y0;
	_mat[1][1] = y1;
	_mat[1][2] = y2;
	_mat[1][3] = y3;
	_mat[2][0] = z0;
	_mat[2][1] = z1;
	_mat[2][2] = z2;
	_mat[2][3] = z3;
	_mat[3][0] = w0;
	_mat[3][1] = w1;
	_mat[3][2] = w2;
	_mat[3][3] = w3;
}

matrix4::matrix4(const float &v)
{
	_mat[0][0] = v;
	_mat[0][1] = 0;
	_mat[0][2] = 0;
	_mat[0][3] = 0;
	_mat[1][0] = 0;
	_mat[1][1] = v;
	_mat[1][2] = 0;
	_mat[1][3] = 0;
	_mat[2][0] = 0;
	_mat[2][1] = 0;
	_mat[2][2] = v;
	_mat[2][3] = 0;
	_mat[3][0] = 0;
	_mat[3][1] = 0;
	_mat[3][2] = 0;
	_mat[3][3] = v;
}

matrix4 matrix4::transpose()
{
	matrix4 trans;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			trans._mat[i][j] = _mat[j][i];
		}
	}
	return trans;
}

bool matrix4::inverse(matrix4& output)
{
	float inv[16], m[16], det;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[4 * i + j] = _mat[j][i];
		}
	}

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0) return false;

	det = 1.0 / det;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			output._mat[j][i] = inv[4 * i + j] * det;
		}
	}
	return true;
}

vector3 matrix4::transformVector(const vector3& v, float hgc)
{
	float x = _mat[0][0] * v._vec[0] + _mat[0][1] * v._vec[1] + _mat[0][2] * v._vec[2] + _mat[0][3] * hgc;
	float y = _mat[1][0] * v._vec[0] + _mat[1][1] * v._vec[1] + _mat[1][2] * v._vec[2] + _mat[1][3] * hgc;
	float z = _mat[2][0] * v._vec[0] + _mat[2][1] * v._vec[1] + _mat[2][2] * v._vec[2] + _mat[2][3] * hgc;
	return vector3(x, y, z);
}

matrix4 matrix4::operator* (const matrix4& T)
{
	matrix4 ans;
	ans._mat[0][0] = _mat[0][0] * T._mat[0][0] + _mat[0][1] * T._mat[1][0] + _mat[0][2] * T._mat[2][0] + _mat[0][3] * T._mat[3][0];
	ans._mat[0][1] = _mat[0][0] * T._mat[0][1] + _mat[0][1] * T._mat[1][1] + _mat[0][2] * T._mat[2][1] + _mat[0][3] * T._mat[3][1];
	ans._mat[0][2] = _mat[0][0] * T._mat[0][2] + _mat[0][1] * T._mat[1][2] + _mat[0][2] * T._mat[2][2] + _mat[0][3] * T._mat[3][2];
	ans._mat[0][3] = _mat[0][0] * T._mat[0][3] + _mat[0][1] * T._mat[1][3] + _mat[0][2] * T._mat[2][3] + _mat[0][3] * T._mat[3][3];
	ans._mat[1][0] = _mat[1][0] * T._mat[0][0] + _mat[1][1] * T._mat[1][0] + _mat[1][2] * T._mat[2][0] + _mat[1][3] * T._mat[3][0];
	ans._mat[1][1] = _mat[1][0] * T._mat[0][1] + _mat[1][1] * T._mat[1][1] + _mat[1][2] * T._mat[2][1] + _mat[1][3] * T._mat[3][1];
	ans._mat[1][2] = _mat[1][0] * T._mat[0][2] + _mat[1][1] * T._mat[1][2] + _mat[1][2] * T._mat[2][2] + _mat[1][3] * T._mat[3][2];
	ans._mat[1][3] = _mat[1][0] * T._mat[0][3] + _mat[1][1] * T._mat[1][3] + _mat[1][2] * T._mat[2][3] + _mat[1][3] * T._mat[3][3];
	ans._mat[2][0] = _mat[2][0] * T._mat[0][0] + _mat[2][1] * T._mat[1][0] + _mat[2][2] * T._mat[2][0] + _mat[2][3] * T._mat[3][0];
	ans._mat[2][1] = _mat[2][0] * T._mat[0][1] + _mat[2][1] * T._mat[1][1] + _mat[2][2] * T._mat[2][1] + _mat[2][3] * T._mat[3][1];
	ans._mat[2][2] = _mat[2][0] * T._mat[0][2] + _mat[2][1] * T._mat[1][2] + _mat[2][2] * T._mat[2][2] + _mat[2][3] * T._mat[3][2];
	ans._mat[2][3] = _mat[2][0] * T._mat[0][3] + _mat[2][1] * T._mat[1][3] + _mat[2][2] * T._mat[2][3] + _mat[2][3] * T._mat[3][3];
	ans._mat[3][0] = _mat[3][0] * T._mat[0][0] + _mat[3][1] * T._mat[1][0] + _mat[3][2] * T._mat[2][0] + _mat[3][3] * T._mat[3][0];
	ans._mat[3][1] = _mat[3][0] * T._mat[0][1] + _mat[3][1] * T._mat[1][1] + _mat[3][2] * T._mat[2][1] + _mat[3][3] * T._mat[3][1];
	ans._mat[3][2] = _mat[3][0] * T._mat[0][2] + _mat[3][1] * T._mat[1][2] + _mat[3][2] * T._mat[2][2] + _mat[3][3] * T._mat[3][2];
	ans._mat[3][3] = _mat[3][0] * T._mat[0][3] + _mat[3][1] * T._mat[1][3] + _mat[3][2] * T._mat[2][3] + _mat[3][3] * T._mat[3][3];
	return ans;
}

matrix4 matrix4::operator* (const float& f)
{
	matrix4 ans(f);
	return *this * ans;
}

matrix4 matrix4::operator + (const matrix4& T)
{
	matrix4 ans;
	ans._mat[0][0] = _mat[0][0] + T._mat[0][0];
	ans._mat[0][1] = _mat[0][1] + T._mat[0][1];
	ans._mat[0][2] = _mat[0][2] + T._mat[0][2];
	ans._mat[0][3] = _mat[0][3] + T._mat[0][3];
	ans._mat[1][0] = _mat[1][0] + T._mat[1][0];
	ans._mat[1][1] = _mat[1][1] + T._mat[1][1];
	ans._mat[1][2] = _mat[1][2] + T._mat[1][2];
	ans._mat[1][3] = _mat[1][3] + T._mat[1][3];
	ans._mat[2][0] = _mat[2][0] + T._mat[2][0];
	ans._mat[2][1] = _mat[2][1] + T._mat[2][1];
	ans._mat[2][2] = _mat[2][2] + T._mat[2][2];
	ans._mat[2][3] = _mat[2][3] + T._mat[2][3];
	ans._mat[3][0] = _mat[3][0] + T._mat[3][0];
	ans._mat[3][1] = _mat[3][1] + T._mat[3][1];
	ans._mat[3][2] = _mat[3][2] + T._mat[3][2];
	ans._mat[3][3] = _mat[3][3] + T._mat[3][3];
	return ans;
}

matrix4 matrix4::operator - (const matrix4& T)
{
	matrix4 ans(-1);
	return *this + (ans * T);
}

ostream& operator<<(ostream& os, const matrix4& m)
{
	cout << '[' << m._mat[0][0] << ", " << m._mat[0][1] << ", " << m._mat[0][2] << ", " << m._mat[0][3] << ']' << endl;
	cout << '[' << m._mat[1][0] << ", " << m._mat[1][1] << ", " << m._mat[1][2] << ", " << m._mat[1][3] << ']' << endl;
	cout << '[' << m._mat[2][0] << ", " << m._mat[2][1] << ", " << m._mat[2][2] << ", " << m._mat[2][3] << ']' << endl;
	cout << '[' << m._mat[3][0] << ", " << m._mat[3][1] << ", " << m._mat[3][2] << ", " << m._mat[3][3] << ']' << endl;
	return os;
}

matrix4::~matrix4()
{
}

vector3::vector3(const float &x0, const float &x1, const float &x2) {
	_vec[0] = x0;
	_vec[1] = x1;
	_vec[2] = x2;
}

float vector3::distance()
{
	return sqrt(_vec[0] * _vec[0] + _vec[1] * _vec[1] + _vec[2] * _vec[2]);
}

vector3 vector3::operator + (const vector3& T)
{
	vector3 ans(_vec[0] + T._vec[0], _vec[1] + T._vec[1], _vec[2] + T._vec[2]);
	return ans;
}

vector3 vector3::operator - (const vector3& T)
{
	vector3 ans(_vec[0] - T._vec[0], _vec[1] - T._vec[1], _vec[2] - T._vec[2]);
	return ans;
}

vector3 vector3::operator + (const vector3& T) const
{
	vector3 ans(_vec[0] + T._vec[0], _vec[1] + T._vec[1], _vec[2] + T._vec[2]);
	return ans;
}

vector3 vector3::operator - (const vector3& T) const
{
	vector3 ans(_vec[0] - T._vec[0], _vec[1] - T._vec[1], _vec[2] - T._vec[2]);
	return ans;
}

vector3 vector3::operator * (const float& f)
{
	vector3 ans(_vec[0] * f, _vec[1] * f, _vec[2] * f);
	return ans;
}

vector3 vector3::operator * (const float& f) const
{
	vector3 ans(_vec[0] * f, _vec[1] * f, _vec[2] * f);
	return ans;
}

vector3 vector3::operator * (const vector3& v)
{
	vector3 ans(_vec[0] * v._vec[0], _vec[1] * v._vec[1], _vec[2] * v._vec[2]);
	return ans;
}

vector3::~vector3()
{

}

ostream& operator<<(ostream& os, const vector3& v)
{
	cout << '[' << v._vec[0] << ", " << v._vec[1] << ", " << v._vec[2] << ']';
	return os;
}

vector3 vector3::normalize(const vector3 &v)
{
	float scalar = sqrt(v._vec[0] * v._vec[0] + v._vec[1] * v._vec[1] + v._vec[2] * v._vec[2]);
	vector3 ans = vector3(v._vec[0] / scalar, v._vec[1] / scalar, v._vec[2] / scalar);
	return ans;
}

vector3 vector3::cross(const vector3 &a, const vector3 &b)
{
	float x = a._vec[1] * b._vec[2] - a._vec[2] * b._vec[1];
	float y = a._vec[2] * b._vec[0] - a._vec[0] * b._vec[2];
	float z = a._vec[0] * b._vec[1] - a._vec[1] * b._vec[0];
	return vector3(x, y, z);
}

float vector3::dot(const vector3 &a, const vector3 &b)
{
	float ans = a._vec[0] * b._vec[0] + a._vec[1] * b._vec[1] + a._vec[2] * b._vec[2];
	return ans;
}
