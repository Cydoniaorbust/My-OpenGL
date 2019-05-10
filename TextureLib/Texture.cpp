#include "stdafx.h"
#include "Texture.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#endif

#include <iostream>

Texture::Texture() : Id(0), Type("simple"), Path("") {}
Texture::Texture(const char *path) : Texture() {
	LoadFromFile(path);
}
Texture::Texture(std::string directory, std::string type, aiString path) : Type(type), Path(path) {
	LoadAssimp(path.C_Str(), directory);
}
Texture::~Texture() {}

void Texture::Bind() { 
	glBindTexture(GL_TEXTURE_2D, Id); 
}
void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::Generate(unsigned char* data, GLenum format, GLuint width, GLuint height) {
	glGenTextures(1, &Id);
	Bind();

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

	Unbind();
}
void Texture::LoadFromFile(const char *path) {
	int width, height, chans;
	unsigned char *data = stbi_load(path, &width, &height, &chans, 0);

	if (data) {
		switch (chans) {
			case 1: Generate(data, GL_RED, width, height); break;
			case 3: Generate(data, GL_RGB, width, height); break;
			default: Generate(data, GL_RGBA, width, height); break;
		}
	}
	else std::cout << "Texture failed to load at path: " << path << std::endl;

	stbi_image_free(data);
}
void Texture::LoadAssimp(const char *path, const std::string &directory) {
	std::string filename(directory + '/' + path);

	int width, height, chans;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &chans, 0);

	if (data) {
		switch (chans) {
			case 1: Generate(data, GL_RED, width, height); break;
			case 3: Generate(data, GL_RGB, width, height); break;
			default: Generate(data, GL_RGBA, width, height); break;
		}
	}
	else std::cout << "Texture failed to load at path: " << path << std::endl;

	stbi_image_free(data);
}