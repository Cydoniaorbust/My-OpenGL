#pragma once

#include <time.h>
#include <iostream>
#include <fstream>
#include <iomanip>
    
#define RND1 (GLfloat)((rand() % 101)/50.)
#define RND2 (GLfloat)((rand() % 151-75)/100.)
#define RND3 (GLfloat)(rand() % 361)
#define SQR(x) ((x)*(x))
#define MIN_val 0.005

using namespace std;

class Fail {
public:
	class SizeMatters {};
	class FailFileRead {};
};

class MyMesh {
	GLfloat	Fig[8] = {
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f
	};
public:
	inline GLfloat S() { return Fig[6] * Fig[7]; };
	inline GLfloat* GetFig() { return Fig; };
	void Rnd() {
		memset(Fig, 0, sizeof(Fig));
		Fig[0] = RND2; Fig[1] = RND2; Fig[2] = RND2;
		Fig[3] = RND3; Fig[4] = RND3; Fig[5] = RND3;
		Fig[6] = RND1; Fig[7] = RND1;
	};
	friend istream &operator >> (istream &, MyMesh &);
	friend ostream &operator << (ostream &, MyMesh &);
	friend ifstream &operator >> (ifstream &, MyMesh &);
	friend ofstream &operator << (ofstream &, MyMesh &);
};

inline istream &operator >> (istream &stream, MyMesh &obj) {
	memset((void*)obj.Fig, 0, sizeof(obj.Fig));
	stream
		>> obj.Fig[0] >> obj.Fig[1] >> obj.Fig[2]
		>> obj.Fig[3] >> obj.Fig[4] >> obj.Fig[5]
		>> obj.Fig[6] >> obj.Fig[7];
	return stream;
};
inline ostream &operator << (ostream &stream, MyMesh &obj) {
	return stream << "\nMyMesh/(x: " << obj.Fig[6] << "|y: " << obj.Fig[7] << ")"; 
};
inline ifstream &operator >> (ifstream &stream, MyMesh &obj) {
	char delim;
	memset((void*)obj.Fig, 0, sizeof(obj.Fig));
	stream >>
		delim >> obj.Fig[0] >> obj.Fig[1] >> obj.Fig[2] >>
		delim >> obj.Fig[3] >> obj.Fig[4] >> obj.Fig[5] >>
		delim >> obj.Fig[6] >>
		delim >> obj.Fig[7];
	return stream;
};
inline ofstream &operator << (ofstream &stream, MyMesh &obj) {
	stream 
		<< "\n" << fixed << setprecision(3)
		<< "\nx " << obj.Fig[6]	
		<< "\ny " << obj.Fig[7] << setprecision(2)
		<< "\nm " << obj.Fig[0] << " " << obj.Fig[1] << " " << obj.Fig[2]
		<< "\nr " << obj.Fig[3] << " " << obj.Fig[4] << " " << obj.Fig[5];
	return stream;
};