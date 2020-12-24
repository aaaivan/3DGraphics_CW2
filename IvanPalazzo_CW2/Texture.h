#ifndef TEXTURE_H
#define TEXTURE_H
#include "Texture.h"
#include <GL/freeglut.h>
#include <string>

class Texture {
	GLuint ID;
	std::string filePath;
	GLint width, height, bytesPerPixel;
public:
	Texture(std::string _filePath);
	~Texture();
	void bind();
	void unbind();
};

#endif // !TEXTURE_H