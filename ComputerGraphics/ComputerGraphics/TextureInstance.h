#pragma once

class TextureInstance
{
public:
	unsigned char* data;
	int width;
	int height;
	int numberOfChannel;

	TextureInstance();
	~TextureInstance();
};

