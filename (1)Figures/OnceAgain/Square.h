#pragma once

#include "Figure.h"

class Square {
	float Fig[18] = {
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,

		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f
	};
public:
	inline float S() { return SQR(Fig[3]); };
	inline float P() { return Fig[3]*4; };
	inline float D() { return (float)(sqrt(
			SQR((Fig[0] + Fig[3] + Fig[6] + Fig[9])/4. + Fig[12]) +
			SQR((Fig[1] + Fig[4] + Fig[7] + Fig[10])/4. + Fig[13]) +
			SQR((Fig[2] + Fig[5] + Fig[8] + Fig[11])/4. + Fig[14]) )
		);
	};
	inline float* GetFig() { return Fig; };
	void Rnd();
	friend istream &operator >> (istream &, Square &);
	friend ostream &operator << (ostream &, Square &);
	friend ifstream &operator >> (ifstream &, Square &);
	friend ofstream &operator << (ofstream &, Square &);
};