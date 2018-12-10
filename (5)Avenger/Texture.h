#pragma once

#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

using UINT = GLuint;
using std::string;

class Texture {
private:
	UINT Width, Height;

	UINT Internal_Format;
	UINT Image_Format;

	UINT Wrap_S;
	UINT Wrap_T;
	UINT Filter_Min;
	UINT Filter_Max;
public:
	GLuint id;
	string type;
	aiString path;

	Texture();
	~Texture();

	static void Generate(UINT w, UINT h, unsigned char* data);
	void Bind() const;
};
