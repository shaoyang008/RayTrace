#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>


using namespace std;
#include "readfile.h"
#include "variables.h"
#include "Transform.h"

void rightmultiply(const matrix4 & M, stack<matrix4> &transfstack) 
{
    matrix4 &T = transfstack.top(); 
    T = T * M;
}

int readvals(const string &s, string &cmd, double* numvals)
{
	size_t pos = s.find(' ');
	size_t start_pos = 0;
	int i = 0;
	cmd = s.substr(start_pos, pos);
	if (cmd == "output") return 1;
	start_pos = s.find_first_not_of(' ', pos);
	while (pos != std::string::npos) {
		pos = s.find(' ', start_pos);
		string val = s.substr(start_pos, pos - start_pos);
		start_pos = s.find_first_not_of(' ', pos);
		numvals[i] = stod(val);
		i++;
	}
	return i;
};

void readfile(const char* filename)
{
	ifstream infile(filename);
	string line;
	stack<matrix4> transforms;
	transforms.push(matrix4(1.0));

	while (getline(infile, line))
	{
		// Remove trailing white spaces
		size_t last_char = line.find_last_not_of(' ');
		line = line.substr(0, last_char+1);
		if (line[0] == '#') continue;
		else if (line.empty()) continue;
		else {
			double vars[10];
			string cmd;
			int varnum = 0;
			varnum = readvals(line, cmd, vars);

			if (cmd == "size") {
				width = vars[0];
				cout << "assigning width: " << width << endl;
				height = vars[1];
				cout << "assigning height: " << height << endl;
			}
			else if (cmd == "maxdepth") {
				maxdepth = vars[0];
				cout << "assigning maxdepth: " << maxdepth << endl;
			}
			else if (cmd == "output") {
				size_t pos = line.find(' ');
				output = line.substr(pos + 1);
				cout << "assigning output: " << output << endl;
			}
			else if (cmd == "camera") {
				lookfrom = vector3(vars[0], vars[1], vars[2]);
				cout << "assigning lookfrom: " << lookfrom << endl;
				lookat = vector3(vars[3], vars[4], vars[5]);
				cout << "assigning lookat: " << lookat << endl;
				cameraup = vector3(vars[6], vars[7], vars[8]);
				cout << "assigning cameraup: " << cameraup<< endl;
				fovy = vars[9];
				cout << "assigning fovy: " << fovy << endl;
			}
			else if (cmd == "sphere") {
				sphere s = sphere(vars[0], vars[1], vars[2], vars[3]);
				s._transform = transforms.top();
				s._ambient = ambient;
				s._emission = emission;
				s._diffuse = diffuse;
				s._specular = specular;
				s._shininess = shininess;
				spheres.push_back(s);
				cout << "assigning " << spheres.size() << " sphere: " << spheres.back() << endl;
			}
			else if (cmd == "maxverts") {
				maxverts = vars[0];
				cout << "assigning maxverts: " << maxverts << endl;
			}
			else if (cmd == "maxvertnorms") {
				cout << "OOPS!! Better do this : maxvertnorms" << endl;
			}
			else if (cmd == "vertex") {
				vector3 v = vector3(vars[0], vars[1], vars[2]);
				vertices.push_back(v);
				cout << "assigning " << vertices.size() <<  " vertex: " << vertices.back() << endl;
			}
			else if (cmd == "vertexnormal") {
				cout << "OOPS!! Better do this : vertexnormal" << endl;
			}
			else if (cmd == "tri") {
				triangle t = triangle(vars[0], vars[1], vars[2]);
				t._transform = transforms.top();
				t._ambient = ambient;
				t._emission = emission;
				t._diffuse = diffuse;
				t._specular = specular;
				t._shininess = shininess;
				triangles.push_back(t);
				cout << "assigning " << triangles.size() << " triangle: " << triangles.back() << endl;
			}
			else if (cmd == "trinormal") {
				cout << "OOPS!! Better do this : trinormal" << endl;
			}
			else if (cmd == "translate") {
				matrix4 trans(1.0);
				trans = Transform::translate(vars[0], vars[1], vars[2]);
				rightmultiply(trans, transforms);
			}
			else if (cmd == "rotate") {
				vector3 axis(vars[0], vars[1], vars[2]);
				matrix4 rotate = Transform::rotate(vars[3], axis);
				rightmultiply(rotate, transforms);

			}
			else if (cmd == "scale") {
				matrix4 scale(1.0);
				scale = Transform::scale(vars[0], vars[1], vars[2]);
				rightmultiply(scale, transforms);
			}
			else if (cmd == "pushTransform") {
				transforms.push(transforms.top());
			}
			else if (cmd == "popTransform") {
				if (transforms.size() <= 1) {
					cerr << "Stack has no elements.  Cannot Pop\n";
				}
				else {
					transforms.pop();
				}
			}
			else if (cmd == "directional") {
				// direction.push_back(vector3(vars[0], vars[1], vars[2]));
				// cout << "assigning direction: " << direction.back() << endl;
				// direction_color.push_back(vector3(vars[3], vars[4], vars[5]));
				// cout << "assigning color: " << direction_color.back() << endl;
				vector3 dir(vars[0], vars[1], vars[2]);
				vector3 color(vars[3], vars[4], vars[5]);
				lights.push_back(light(dir, color, "directional"));
			}
			else if (cmd == "point") {
				// point.push_back(vector3(vars[0], vars[1], vars[2]));
				// cout << "assigning point: " << point.back() << endl;
				// point_color.push_back(vector3(vars[3], vars[4], vars[5]));
				// cout << "assigning color: " << point_color.back() << endl;
				vector3 dir(vars[0], vars[1], vars[2]);
				vector3 color(vars[3], vars[4], vars[5]);
				lights.push_back(light(dir, color, "point"));
			}
			else if (cmd == "attenuation") {
				attenuation = vector3(vars[0], vars[1], vars[2]);
				cout << "assigning attenuation: " << attenuation << endl;
			}
			else if (cmd == "ambient") {
				ambient = vector3(vars[0], vars[1], vars[2]);
				cout << "assigning ambient: " << ambient << endl;
			}
			else if (cmd == "diffuse") {
				diffuse = vector3(vars[0], vars[1], vars[2]);
				cout << "assigning diffuse: " << diffuse << endl;
			}
			else if (cmd == "specular") {
				specular = vector3(vars[0], vars[1], vars[2]);
				cout << "assigning specular: " << specular << endl;
			}
			else if (cmd == "shininess") {
				shininess = vars[0];
				cout << "assigning shininess: " << shininess << endl;
			}
			else if (cmd == "emission") {
				emission = vector3(vars[0], vars[1], vars[2]);
				cout << "assigning emission: " << emission << endl;
			}
			else {
				cout << "Unknown command " << cmd << endl;
			}
		}
	}
}
