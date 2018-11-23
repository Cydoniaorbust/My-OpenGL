#include "Triangle.h"

void Triangle::Rnd() {
	memset(Fig, 0, sizeof(Fig));
	Fig[3] = RND1; Fig[6] = RND1; Fig[7] = RND1;
	Fig[9] = RND2; Fig[10] = RND2; Fig[11] = RND2;
	Fig[12] = RND3; Fig[13] = RND3; Fig[14] = RND3;
};
istream &operator >> (istream &stream, Triangle &obj) {
	memset(obj.Fig, 0, sizeof(obj.Fig));
	stream >> obj.Fig[3] >> obj.Fig[6] >> obj.Fig[7]
		>> obj.Fig[9] >> obj.Fig[10] >> obj.Fig[11]
		>> obj.Fig[12] >> obj.Fig[13] >> obj.Fig[14];
	return stream;
};
ostream &operator << (ostream &stream, Triangle &obj) {
	stream << "\n/(x: " << obj.Fig[3] << "|x: " << obj.Fig[6] << " y: " << obj.Fig[7]<< ")";
	return stream;
};
ifstream &operator >> (ifstream &stream, Triangle &obj) {
	char delim;
	memset(obj.Fig, 0, sizeof(obj.Fig));
	stream >>
		delim >> obj.Fig[3] >> 
		delim >> obj.Fig[6] >>
		delim >> obj.Fig[7] >>
		delim >> obj.Fig[9] >> obj.Fig[10] >> obj.Fig[11] >>
		delim >> obj.Fig[12] >> obj.Fig[13] >> obj.Fig[14];
	return stream;
};
ofstream &operator << (ofstream &stream, Triangle &obj) {
	stream << "\n" << fixed << setprecision(3)
		<< "\nx " << obj.Fig[3]
		<< "\nx " << obj.Fig[6]
		<< "\ny " << obj.Fig[7] << setprecision(2)
		<< "\nm " << obj.Fig[9] << " " << obj.Fig[10] << " " << obj.Fig[11]
		<< "\nr " << obj.Fig[12] << " " << obj.Fig[13] << " " << obj.Fig[14];
	return stream;
};