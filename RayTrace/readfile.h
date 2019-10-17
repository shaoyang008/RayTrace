// Readfile definitions 

#ifndef READ_FILE_H
#define READ_FILE_H

// void matransform (stack<mat4> &transfstack, GLfloat * values) ;
// void rightmultiply (const mat4 & M, stack<mat4> &transfstack) ;
int readvals(const string &s, string &cmd, double* numvals);
void readfile(const char * filename);

#endif // !1