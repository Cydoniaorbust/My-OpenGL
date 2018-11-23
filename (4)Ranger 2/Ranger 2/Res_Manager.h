#pragma once

#include "Study/Texture.h"
#include "Study/Shader.h"

#include <glad/glad.h>

#include <map>
using std::map;
#include <string>

class Res_Manager {
private:
	map<string, Shader>    Shaders;
	map<string, Texture2D> Textures;
public:
	Res_Manager() {}
	
	Shader		GetShader(string);
	Texture2D	GetTexture(string);

	void		LoadShader(const char*, const char*, string);
	void		LoadShader(const char*, const char*, const char*, string);
	Texture2D	LoadTexture(const char*, GLboolean, string);
	Texture2D	loadTextureFromFile(const char*, GLboolean);

	void		Clear();
};