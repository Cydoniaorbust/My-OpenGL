#pragma once 

#include "Figure.h"

template <class Model>
class TFigureMatrix
{
	size_t N = 10;
	vector<Model> array;
	ifstream fin;
	ofstream fout;
public:
	vector<vec3> Verts;
	vector<GLuint> Indices;

	TFigureMatrix() { array.resize(N); };
	size_t GetN() { return N; };
	GLfloat* GetFigArr(size_t i) { return array[i].GetFig(); };
	
	void Num() {
		try {
			cin >> N;
			array.resize(N);
		}
		catch (...) {
			cerr << "Used non-digit symbols!\nN reset to default value.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			N = 10;
		}
	};

	void SetRandVal(size_t i) { do array[i].Rnd(); while (array[i].S() < MIN_val); };
	void ReadTxt() {
		fin.open("Res/Mesh.txt");
		char delim;
		try {
			fin >> delim;
			if (delim != 'd') throw Fail::FailFileRead();
			fin >> N;
			array.resize(N);
			for (size_t i = 0; i < N; i++) fin >> array[i];
		}
		catch (...) {
			cerr << "Failed to read from file!\n";
			fin.clear();
			fin.ignore(numeric_limits<streamsize>::max(), '\n');
			fin.close();
			throw Fail();
		}
		fin.close();
	};
	void Show() {
		for (size_t i = 0; i < N; i++) cout << array[i];
		cout << endl;
	};
	void GenRandVals() {
		Num();
		for (size_t i = 0; i < N; i++) SetRandVal(i);
	};

	void ImportObjFile() {
		try {
			fin.open("C:/Google Диск/Resources/Model/Alien.obj");
			if (!fin.is_open()) throw Fail::FailFileRead();
			ReadObjFile();
		}
		catch (...) {
			cerr << "Failed to read from file!\n";
			fin.clear();
			fin.ignore(numeric_limits<streamsize>::max(), '\n');
			fin.close();
		}
	}
	void ReadObjFile() {
		char c;
		while (!fin.eof()) {
			fin.get(c);
			switch (c) {
			case 'v': ReadVertexInfo();	break;
			case 'f': ReadFaceInfo(); break;
			default: break;
			}
		}
	}
	void ReadVertexInfo() {
		string s;

		vec3 NewVertex;
		fin >> NewVertex.x >> NewVertex.y >> NewVertex.z;
		Verts.push_back(NewVertex);

		getline(fin, s, '\n');
	}
	void ReadFaceInfo() {
		string s;
		
		for (int i = 0; i < 3; i++) {
			getline(fin, s, ' ');
			getline(fin, s, '/');
			Indices.push_back(stoi(s)-1);
		}

		getline(fin, s, '\n');
	}
};