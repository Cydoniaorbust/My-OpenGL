#include "Texture.h"

Texture::Texture() :
	Width(0),
	Height(0),
	Internal_Format(GL_RGB),
	Image_Format(GL_RGB),
	Wrap_S(GL_REPEAT),
	Wrap_T(GL_REPEAT),
	Filter_Min(GL_LINEAR),
	Filter_Max(GL_LINEAR) {
	glGenTextures(1, &id);
} {}
Texture::~Texture() {}

void Texture::Generate(UINT w, UINT h, unsigned char* data) {
	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, w, h, 0, Image_Format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max);

	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::Bind() const { glBindTexture(GL_TEXTURE_2D, id); }