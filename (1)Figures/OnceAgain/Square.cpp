#include "Square.h"

void Square::Rnd() {
	memset(Fig, 0, sizeof(Fig));
	Fig[3] = RND1; 
	Fig[12] = RND2; Fig[13] = RND2; Fig[14] = RND2;
	Fig[15] = RND3;	Fig[16] = RND3;	Fig[17] = RND3;
	Fig[7] = Fig[3]; Fig[9] = Fig[3]; Fig[10] = Fig[3];
};
istream &operator >> (istream &stream, Square &obj) {
	memset(obj.Fig, 0, sizeof(obj.Fig));
	stream >> obj.Fig[3] >> obj.Fig[7] >> obj.Fig[9] >> obj.Fig[10]
		>> obj.Fig[12] >> obj.Fig[13] >> obj.Fig[14]
		>> obj.Fig[15] >> obj.Fig[16] >> obj.Fig[17];
	return stream;
};
ostream &operator << (ostream &stream, Square &obj) {
	stream << "\n/(x: " << obj.Fig[3] << ")";
	return stream;
};
ifstream &operator >> (ifstream &stream, Square &obj) {
	char delim;
	memset(obj.Fig, 0, sizeof(obj.Fig));
	stream >>
		delim >> obj.Fig[3] >>
		delim >> obj.Fig[7] >>
		delim >> obj.Fig[9] >>
		delim >> obj.Fig[10] >>
		delim >> obj.Fig[12] >> obj.Fig[13] >> obj.Fig[14] >>
		delim >> obj.Fig[15] >> obj.Fig[16] >> obj.Fig[17];
	return stream;
};
ofstream &operator << (ofstream &stream, Square &obj) {
	stream << "\n" << fixed << setprecision(3)
		<< "\nx " << obj.Fig[3]
		<< "\ny " << obj.Fig[7]
		<< "\nx " << obj.Fig[9]
		<< "\ny " << obj.Fig[10] << setprecision(2)
		<< "\nm " << obj.Fig[12] << " " << obj.Fig[13] << " " << obj.Fig[14]
		<< "\nr " << obj.Fig[15] << " " << obj.Fig[16] << " " << obj.Fig[17];
	return stream;
};