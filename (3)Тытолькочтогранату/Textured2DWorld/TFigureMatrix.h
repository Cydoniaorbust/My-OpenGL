#pragma once

template <class Model>
class TFigureMatrix {
	std::ifstream fin;
	std::ofstream fout;
public:
	std::vector<glm::vec3> Verts;
	std::vector<GLuint> Indices;

	void ImportObjFile() {
		try {
			fin.open("Res/Alien.obj");
			if (!fin.is_open()) throw Fail::FailFileRead();
			ReadObjFile();
		}
		catch (...) {
			std::cerr << "Failed to read from file!\n";
			fin.clear();
			fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
		std::string s;

		glm::vec3 NewVertex;
		fin >> NewVertex.x >> NewVertex.y >> NewVertex.z;
		Verts.push_back(NewVertex);

		std::getline(fin, s, '\n');
	}
	void ReadFaceInfo() {
		std::string s;
		
		for (int i = 0; i < 3; i++) {
			std::getline(fin, s, ' ');
			std::getline(fin, s, '/');
			Indices.push_back(std::stoi(s)-1);
		}

		std::getline(fin, s, '\n');
	}
};