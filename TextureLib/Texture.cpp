#include "stdafx.h"
#include "Texture.h"

#include <iostream>

void Texture2D::Bind(GLuint Id) { 
	glBindTexture(GL_TEXTURE_2D, Id); 
}
GLuint Texture2D::Generate(unsigned char* data, GLuint width, GLuint height) {
	GLuint Id;
	glGenTextures(1, &Id);

	Bind(Id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Bind(0);
	return Id;
}