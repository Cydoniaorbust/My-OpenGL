#include "Texture.h"

#include <iostream>

#pragma region Ctor/Dtor

Texture2D::Texture2D() :
	Width(0),
	Height(0),
	InternalFormat(GL_RGB),
	ImageFormat(GL_RGB),
	WrapS(GL_REPEAT),
	WrapT(GL_REPEAT),
	FilterMin(GL_LINEAR),
	FilterMax(GL_LINEAR) {
	glGenTextures(1, &Id);
}
Texture2D::Texture2D(const Texture2D & t) : Id(t.GetId()) {}
Texture2D::Texture2D(Texture2D &&t) : Texture2D(t) { t.SetId(0); }
Texture2D::~Texture2D() {}

Texture2D::Texture2D(int param) : Texture2D() {}

#pragma endregion

#pragma region Set/Get

int Texture2D::GetId() const noexcept { return Id; }
void Texture2D::SetId(int id) { Id = id; }

#pragma endregion

#pragma region Methods

void Texture2D::Generate(GLuint width, GLuint height, unsigned char* data) {
	Width = width;
	Height = height;

	glBindTexture(GL_TEXTURE_2D, Id);
	glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, width, height, 0, ImageFormat, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterMax);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const { glBindTexture(GL_TEXTURE_2D, Id); }

#pragma endregion

#pragma region Copy

void Texture2D::Swap(Texture2D &t) {
	//std::swap(t.Id, Id);
}
Texture2D& Texture2D::operator=(const Texture2D &t) {
	if (this != &t) Texture2D(t).Swap(*this);
	return *this;
}
Texture2D& Texture2D::operator=(Texture2D &&t) {
	Swap(t);
	return *this;
}

#pragma endregion