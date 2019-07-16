#include "stdafx.h"
#include "Texture.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#endif

void Texture::Bind() { glBindTexture(GL_TEXTURE_2D, Id); }
void Texture::Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
void Texture::Generate(unsigned char* data, GLenum format, GLuint width, GLuint height) {
	glGenTextures(1, &Id);
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	Unbind();
}
void Texture::LoadFromFile(std::string path) {
	int width, height, chans;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &chans, 0);

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

Texture::Texture() : Id(0), Type(""), Path("") {}
Texture::Texture(std::string path, std::string type) : Type(type), Path(path) { LoadFromFile(path); }
Texture::Texture(const Texture &t) : Type(t.Type), Path(t.Path) { LoadFromFile(Path); }
Texture::Texture(Texture &&t) : Type(t.Type), Path(t.Path) { LoadFromFile(Path); t.~Texture(); }
Texture::~Texture() { glDeleteTextures(1, &Id); }

void Texture::Swap(Texture &t) {
	std::swap(Id, t.Id);
	std::swap(Type, t.Type);
	std::swap(Path, t.Path);
}
Texture& Texture::operator=(const Texture &t) {
	if (this != &t) Texture(t).Swap(*this);
	return *this;
}
Texture& Texture::operator=(Texture &&t) {
	Swap(t);
	return *this;
}