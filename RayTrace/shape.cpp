#include <algorithm>
#include "shape.h"
#include "variables.h"

sphere::sphere()
{
}

sphere::sphere(const float &x, const float &y, const float &z, const float &r)
{
	_center = vector3(x, y, z);
	_radius = r;
}

float sphere::intersects(vector3 ray, vector3 dir) {
	matrix4 invTrans;
	if (_transform.inverse(invTrans)) {
		ray = invTrans.transformVector(ray, 1);
		dir = invTrans.transformVector(dir, 0);
	}
	float t;
	float a = vector3::dot(dir, dir);
	float b = 2 * vector3::dot(dir, (ray - _center));
	float c = vector3::dot((ray - _center), (ray - _center)) - _radius * _radius;
	float delta = b * b - (4 * a * c);
	if (delta < 0) return -1;
	else {
		float t1 = (-1 * b + sqrt(delta)) / (2 * a);
		float t2 = (-1 * b - sqrt(delta)) / (2 * a);
		if (t1 >= 0 && t2 >= 0) {
			t = min(t1, t2);
			_hitPoint = _transform.transformVector((ray + dir * t), 1);
			vector3 o = _transform.transformVector(ray, 1);
			float distance = (_hitPoint - o).distance();
			if (distance > THRESHOLD) {
				_normal = vector3::normalize(invTrans.transpose().transformVector((ray + dir * t - _center), 1));
				return distance;
			}
			else {
				t = max(t1, t2);
			}
		}
		else if (t1 >= 0 && t2 < 0) t = t1;
		else if (t2 >= 0 && t1 < 0) t = t2;
		else return -1;
	}
	_hitPoint = _transform.transformVector((ray + dir * t), 1);
	vector3 o = _transform.transformVector(ray, 1);
	float distance = (_hitPoint - o).distance();
	if (distance > THRESHOLD) {
		_normal = vector3::normalize(invTrans.transpose().transformVector((ray + dir * t - _center), 1));
		return distance;
	}
	else return -1;
}


sphere::~sphere()
{
}

ostream& operator<<(ostream& os, const sphere& s)
{
	cout << "center: " << s._center << ", radius: " << s._radius;
	return os;
}

triangle::triangle()
{
}

triangle::triangle(const float &v1, const float &v2, const float &v3)
{
	_vertices[0] = v1;
	_vertices[1] = v2;
	_vertices[2] = v3;
}

float triangle::intersects(vector3 ray, vector3 dir)
{
	matrix4 invTrans;
	if (_transform.inverse(invTrans)) {
		ray = invTrans.transformVector(ray, 1);
		dir = invTrans.transformVector(dir, 0);
	}
	vector3 AB = vertices[_vertices[0]] - vertices[_vertices[1]];
	vector3 AC = vertices[_vertices[0]] - vertices[_vertices[2]];
	vector3 normal = vector3::normalize(vector3::cross(AB, AC));
	if (vector3::dot(dir, normal) == 0) return -1;
	float t = (vector3::dot(vertices[_vertices[0]], normal) - vector3::dot(ray, normal)) / vector3::dot(dir, normal);
	if (t <= 0) return -1;
	vector3 p = ray + dir * t;
	vector3 tmp = p - vertices[_vertices[0]];
	vector3 BA = AB * -1;
	vector3 CA = AC * -1;
	float b0 = BA._vec[0] + BA._vec[2];
	float c0 = CA._vec[0] + CA._vec[2];
	float b1 = BA._vec[1] + BA._vec[2];
	float c1 = CA._vec[1] + CA._vec[2];

	float beta = ((tmp._vec[0] + tmp._vec[2]) * c1 - (tmp._vec[1] + tmp._vec[2]) * c0) / (b0 * c1 - b1 * c0);
	float gamma = ((tmp._vec[0] + tmp._vec[2]) * b1 - (tmp._vec[1] + tmp._vec[2]) * b0) / (b1 * c0 - b0 * c1);
	float alpha = 1 - beta - gamma;
	if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1) {
		_hitPoint = _transform.transformVector((ray + dir * t), 1);
		_normal = vector3::normalize(invTrans.transpose().transformVector(normal, 0));
		vector3 o = _transform.transformVector(ray, 1);
		float distance = (_hitPoint - o).distance();
		if (distance > THRESHOLD) return distance;
	}
	
	return -1;
}

triangle::~triangle()
{
}

ostream& operator<<(ostream& os, const triangle& t)
{
	cout << "vertices index: " << t._vertices[0] << ", " << t._vertices[1] << ", " << t._vertices[2];
	return os;
}