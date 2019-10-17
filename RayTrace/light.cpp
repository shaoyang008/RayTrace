#include "light.h"
#include "variables.h"
#include <algorithm>

light::light()
{
}

light::light(const vector3& p, const vector3& c, const string& t)
{
	_position = p;
	_color = c;
	_type = t;
}

light::~light()
{
}

bool light::vec2rgb(vector3 color, unsigned char &r, unsigned char &g, unsigned char &b)
{
	float maxValue = 1.0;
	r = 0xFF * min(color._vec[0], maxValue);
	g = 0xFF * min(color._vec[1], maxValue);
	b = 0xFF * min(color._vec[2], maxValue);
	return true;
}

vector3 light::attenColor(const vector3& c, const float& distance)
{
	float atten = attenuation._vec[0] + attenuation._vec[1] * distance + attenuation._vec[2] * distance * distance;
	atten = 1.0f / atten;
	return c * atten;
}