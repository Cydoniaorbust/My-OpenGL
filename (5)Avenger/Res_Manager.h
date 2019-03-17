#pragma once

#include "Model.h"

class Res_Manager {
public:
	vector<GLuint> AllShaders;
	vector<Model> AllObjects;
	//vector<Texture> AllTextures;

	Res_Manager() {}
	~Res_Manager() {}
};