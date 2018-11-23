#include "Res_Manager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <sstream>
#include <fstream>

Shader		Res_Manager::GetShader(string name) { return Shaders[name]; }
Texture2D	Res_Manager::GetTexture(string name) { return Textures[name]; }

void		Res_Manager::LoadShader(const char* vPath, const char* fPath, string name) {
	Shader temp(vPath, fPath);
	Shaders[name] = temp;
}
void		Res_Manager::LoadShader(const char* vPath, const char* fPath, const char* gPath, string name) {
	Shader temp(vPath, fPath, gPath);
	Shaders[name] = temp;
}
Texture2D	Res_Manager::LoadTexture(const char* file, GLboolean alpha, string name) {
	Textures[name] = loadTextureFromFile(file, alpha);
}
Texture2D	Res_Manager::loadTextureFromFile(const char* file, GLboolean alpha) {
	Texture2D texture;
	int width, height, chans = 3;

	if (alpha) {
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
		chans = 4;
	}
	unsigned char *image = stbi_load(file, &width, &height, &chans, 0);
	if (image) texture.Generate(width, height, image);
	else std::cout << "Texture failed to load at path: " << file << std::endl;
	stbi_image_free(image);

	return texture;
}

void		Res_Manager::Clear() {
	for (auto iter : Shaders) glDeleteProgram(iter.second.GetId());
	for (auto iter : Textures) glDeleteTextures(1, &iter.second.ID);
}