#ifndef GRASS_H
#define GRASS_H
#include "Texture.h"
#include <GL/freeglut.h>
#include <vector>

class Grass
{
	GLfloat width, length;
	static Texture* texture;
	std::vector<GLfloat> vertCoord = {
		1,0,-1,
		-1,0,-1,
		-1,0,0,
		1,0,0,
	};
	std::vector<GLfloat> textCoord = {
		1,1,
		0,1,
		0,0,
		1,0,
	};
	std::vector<GLfloat> vertNormals = {
		0,1,0,
		0,1,0,
		0,1,0,
		0,1,0,
	};
public:
	Grass(GLfloat _width, GLfloat _length);
	static void loadTexture();
	static void unloadTexture();
	void draw();
};

#endif // !GRASS_H


