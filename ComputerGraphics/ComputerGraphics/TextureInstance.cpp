#include "stdafx.h"
#include "TextureInstance.h"


TextureInstance::TextureInstance()
{
	data = nullptr;
	width = 0;
	height = 0;
	numberOfChannel = 0;
}

TextureInstance::~TextureInstance()
{
	//stbi_image_free(data);
}
