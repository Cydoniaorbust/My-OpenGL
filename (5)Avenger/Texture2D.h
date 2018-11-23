#pragma once

#include <glad/glad.h>
#include <iostream>
//#include "Model.h"

#define UINT GLuint

class Texture2D {
public:
	UINT ID;

	UINT Width, Height;

	UINT Internal_Format;
	UINT Image_Format;

	UINT Wrap_S;
	UINT Wrap_T;
	UINT Filter_Min;
	UINT Filter_Max;

	Texture2D();

	void Generate(UINT w, UINT h, unsigned char* data);

	void Bind() const;
};