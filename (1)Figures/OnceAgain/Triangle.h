#pragma once

#include "Figure.h"

#define Len2(i, j) sqrt(SQR(Fig[i*3] - Fig[j*3]) + SQR(Fig[1+i*3] - Fig[1+j*3]))

class Triangle {
	float Fig[15] = {
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,

		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f
	};
public:
	inline float P() { return Len2(0, 1) + Len2(0, 2) + Len2(1, 2); };
	inline float S() { float hP = P() / 2.0f; return sqrt(hP*(hP - Len2(0, 1))*(hP - Len2(0, 2))*(hP - Len2(1, 2))); };
	inline float D() { return (float)sqrt(
			SQR((Fig[0] + Fig[3] + Fig[6]) / 3. + Fig[9]) +
			SQR((Fig[1] + Fig[4] + Fig[7]) / 3. + Fig[10]) +
			SQR((Fig[2] + Fig[5] + Fig[8]) / 3. + Fig[11]));
	};
	inline float* GetFig() { return Fig; };
	void Rnd();
	friend istream &operator >> (istream &, Triangle &);
	friend ostream &operator << (ostream &, Triangle &);
	friend ifstream &operator >> (ifstream &, Triangle &);
	friend ofstream &operator << (ofstream &, Triangle &);
};