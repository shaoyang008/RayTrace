#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <stack>
#include <algorithm>
#include <FreeImage.h>


using namespace std; 

// Main variables in the program.  
#include "readfile.h"
#include "math.h"
#include "variables.h"
#include "Transform.h"
#include "light.h"

int height;
int width;
int maxdepth;
string output;

// Camera
vector3 lookfrom;
vector3 lookat;
vector3 cameraup;
float fovy;

// Lights
vector<light> lights;
vector3 attenuation;
vector3 ambient;

// Geomerty
int maxverts;
vector<sphere> spheres;
vector<vector3> vertices;
vector<triangle> triangles;

// Materials
vector3 diffuse;
vector3 specular;
vector3 emission;
float shininess;

int MAX_DISTANCE = 100000;
float THRESHOLD = 0.001;

vector3 computeLight(vector3 direction, vector3 color, vector3 normal, vector3 half, vector3 diffuse, vector3 specular, float shininess) {
	float nDotL = vector3::dot(normal, direction);
	//vec4 lambert = mydiffuse * lightcolor * max(nDotL, 0.0);
	vector3 lambert = diffuse * color * max(nDotL, (float)0.0);
	// cout << lambert << ", " << nDotL << endl;

	float nDotH = vector3::dot(normal, half);
	//vec4 phong = myspecular * lightcolor * pow(max(nDotH, 0.0), myshininess);
	vector3 phong = specular * color * pow(max(nDotH, float(0.0)), shininess);

	//vec4 retval = lambert + phong;
	vector3 retval = lambert + phong;
	return retval;
}

float iterateShapes(shape& hit_shape, vector3 start, vector3 dir)
{
	float min_dist = MAX_DISTANCE;
	// cout << "Calculating sphere ... " << spheres.size() << endl;
	for (int m = 0; m < spheres.size(); m++) {
		float dist = spheres[m].intersects(start, dir);
		if (dist > 0 && dist < min_dist) {
			min_dist = dist;
			hit_shape = spheres[m];
		}
	}
	// cout << "Calculating triangles ... " << triangles.size() << endl;
	for (int n = 0; n < triangles.size(); n++) {
		float dist = triangles[n].intersects(start, dir);
		if (dist > 0 && dist < min_dist) {
			min_dist = dist;
			hit_shape = triangles[n];
		}
	}
	return min_dist;
}

vector3 colorPixels(const shape * obj, const vector3 hit_point, const vector3 hit_normal, vector3 inputRay, int depth)
{	
	shape hit_shape;
	vector3 finalcolor = obj->_ambient + obj->_emission;
	vector3 reflect;
	
	if (depth < maxdepth) {
		vector3 w = inputRay - hit_normal * 2 * vector3::dot(inputRay, hit_normal);
		float min_dist = iterateShapes(hit_shape, hit_point, w);
		if (min_dist > 0 && min_dist < MAX_DISTANCE) {
			reflect = colorPixels(&hit_shape, hit_shape._hitPoint, hit_shape._normal, w, depth + 1);
			finalcolor = finalcolor + light::attenColor(reflect * obj->_specular, (hit_point - hit_shape._hitPoint).distance());
		}
	}

	for (int i = 0; i < lights.size(); i++) {
		// Check object hits
		vector3 objDir = lights[i]._position - hit_point;
		float obj_dist = objDir.distance();
		float min_dist = iterateShapes(hit_shape, hit_point, objDir);
		if (min_dist < MAX_DISTANCE && min_dist <= obj_dist) {
			continue;
		}
		else {
			vector3 _direction;
			if (lights[i]._type == "directional") {
				_direction = vector3::normalize(lights[i]._position);
			}
			else {
				_direction = vector3::normalize(lights[i]._position - hit_point); // no attenuation 
			}
			// vector3 eyedir = vector3::normalize(lookfrom - hit_point);
			vector3 eyedir = inputRay * -1;
			vector3 _half = vector3::normalize(_direction + eyedir);
			vector3 _col = light::attenColor(computeLight(_direction, lights[i]._color, hit_normal, _half, obj->_diffuse, obj->_specular, obj->_shininess), obj_dist);
			// vector3 _col = computeLight(_direction, lights[i]._color, hit_normal, _half, obj->_diffuse, obj->_specular, obj->_shininess);
			finalcolor = finalcolor + _col;
		}
	}
	return finalcolor;
}

bool initVars()
{
	// Initialize
	output = "test.png";
	ambient = vector3(0.2, 0.2, 0.2);
	attenuation = vector3(1, 0, 0);
	diffuse = vector3(0, 0, 0);
	specular = vector3(0, 0, 0);
	emission = vector3(0, 0, 0);
	shininess = 0;
	maxdepth = 5;
	return true;
}


int main(int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Wrong number of inputs.";
		getchar();
		return -1;
	}

	initVars();
	readfile(argv[1]);

	// Setup coordinates
	vector3 w = vector3::normalize(lookat - lookfrom);
	vector3 u = vector3::normalize(vector3::cross(cameraup, w));
	vector3 v = vector3::cross(w, u);

	// Calculate each pixels
	BYTE* colorMap = new BYTE[3 * width * height];
	float fovx = atan((width / 2) * tan(fovy * pi / 360) / (height / 2)) * 360 / pi;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int index = 3 * (i * width + j);
			float alpha = tan(fovx * pi / 360) * ((width / 2) - j - 0.5) / (width / 2);
			float beta = tan(fovy * pi / 360) * ((height / 2) - i - 0.5) / (height / 2);
			vector3 dir = vector3::normalize(u * alpha + v * beta + w);

			colorMap[index] = 0x00;
			colorMap[index + 1] = 0x00;
			colorMap[index + 2] = 0x00;

			// cout << lookfrom << ", " << dir << endl;
			shape hit_shape;
			float min_dist = iterateShapes(hit_shape, lookfrom, dir);

			// cout << "Determine colors" << endl;
			if (min_dist > 0 && min_dist < MAX_DISTANCE) {
				vector3 finalColor = colorPixels(&hit_shape, hit_shape._hitPoint, hit_shape._normal, vector3::normalize(hit_shape._hitPoint - lookfrom), 0);
				light::vec2rgb(finalColor, colorMap[index + 2], colorMap[index + 1], colorMap[index]);
			}
			if(index % 100 == 0 ) cout << index << " pixels finished" << endl;
		}
	}
	// End
	FreeImage_Initialise();
	cout << "Creating Image..." << endl;
	FIBITMAP *img = FreeImage_ConvertFromRawBits(colorMap, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
	cout << "Saving..." << endl;
	FreeImage_Save(FIF_PNG, img, output.c_str(), 0);
	cout << "All Done";
	FreeImage_DeInitialise();
	// getchar();
	return 0;
}
