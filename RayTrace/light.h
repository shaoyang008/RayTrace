#ifndef LIGHT_H
#define LIGHT_H
#include "math.h"

class light
{
public:
	light();
	light(const vector3& p, const vector3& c, const string& t);
	vector3 getColor(const float& distance);
	~light();
	static bool vec2rgb(vector3 co, unsigned char &r, unsigned char &g, unsigned char &b);
	static vector3 attenColor(const vector3& c, const float& distance);

	vector3 _position;
	vector3 _color;
	string _type;
};
#endif // !LIGHT_H
#pragma once
