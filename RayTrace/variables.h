#ifndef VARIABLES
#define VARIABLES
#include <vector>

#include "math.h"
#include "shape.h"
#include "light.h"

using namespace std;

// Image Setups
extern int height;
extern int width;
extern int maxdepth;
extern string output;

// Camera
extern vector3 lookfrom;
extern vector3 lookat;
extern vector3 cameraup;
extern float fovy;

// Lights
extern vector<light> lights;
extern vector3 attenuation;
extern vector3 ambient;

// Geomerty
extern int maxverts;
extern vector<sphere> spheres;
extern vector<vector3> vertices;
extern vector<triangle> triangles;

// Materials
extern vector3 diffuse;
extern vector3 specular;
extern vector3 emission;
extern float shininess;

extern float THRESHOLD;
#endif