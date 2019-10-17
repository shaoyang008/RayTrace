#ifndef SHAPE_H
#define SHAPE_H

#include "math.h"
#include <iostream>


using namespace std;

class shape
{
public:
	shape() {};
	~shape() {};
	// virtual vector3 normal() const { cout << "Hello"; return vector3(0, 0, 0); };

	vector3 _normal;
	vector3 _hitPoint;
	matrix4 _transform;
	vector3 _ambient, _emission, _diffuse, _specular;
	float _shininess;
};

class sphere : public shape
{
public:
	sphere();
	sphere(const float &x, const float &y, const float &z, const float &r);
	float intersects(vector3 ray, vector3 dir);
	~sphere();

	friend ostream& operator<<(ostream& os, const sphere& s);

	vector3 _center;
	float _radius;
};

class triangle : public shape
{
public:
	triangle();
	triangle(const float &v1, const float &v2, const float &v3);
	float intersects(vector3 ray, vector3 dir);
	~triangle();

	friend ostream& operator<<(ostream& os, const triangle& t);

	int _vertices[3];
};
#endif
