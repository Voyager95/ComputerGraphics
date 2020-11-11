#pragma once
#include "stdafx.h"

class TextureInstance
{
public:
	unsigned char* data;
	int width;
	int height;
	int numberOfChannel;

	GLuint texture;

	TextureInstance();
	~TextureInstance();
};

