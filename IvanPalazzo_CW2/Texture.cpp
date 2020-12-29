#include "Texture.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture(std::string _filePath):
ID(0), filePath(_filePath), width(0),
height(0), bytesPerPixel(0) {
	//textures are processed from the top-left pixel
	//but the origin of the texture coordinates is the bottom-left
	//hence flip the picture before processing
	stbi_set_flip_vertically_on_load(1);
	//convert image into an array of unsigned chars (1 pixel = 4 elements)
	unsigned char* localBuffer = stbi_load(
		filePath.c_str(), &width, &height, &bytesPerPixel, 4);
	if (localBuffer) {//if the converson was successful
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		//specify wrap, minification and magnification properties
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//load texture into memory
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);
		//free memory allocated for the buffer, which is no longer needed
		stbi_image_free(localBuffer);
	}
}

//destructor: free up memory occupied by texture
Texture::~Texture() {
	glDeleteTextures(1, &ID);
}

//bind texture to the active texture unit
void Texture::bind(){
	glBindTexture(GL_TEXTURE_2D, ID);
}

//unbind texture
void Texture::unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}
