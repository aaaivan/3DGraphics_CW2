#include "Texture.h"
#include "stb_image.h"
#include <iostream>
Texture::Texture(std::string _filePath):
ID(0), filePath(_filePath), width(0),
height(0), bytesPerPixel(0) {

	stbi_set_flip_vertically_on_load(1);
	unsigned char* localBuffer = stbi_load(
		filePath.c_str(), &width, &height, &bytesPerPixel, 4);
	if (localBuffer) {
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(localBuffer);
	}
}

Texture::~Texture() {
	glDeleteTextures(1, &ID);
}

void Texture::bind(){
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}
