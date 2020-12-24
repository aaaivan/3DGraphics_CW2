#ifndef SLIDER_H
#define SLIDER_H
#include "Texture.h"
#include <vector>
#include <GL/freeglut.h>

class Slider{
	enum Orientation {
		HORIZONTAL, VERTICAL
	};
	GLfloat value;
	Orientation orientation;
	GLfloat width;
	GLfloat height;
	std::vector<Texture*> textures;
public:
	Slider(Orientation _orientation, GLfloat _width, GLfloat _height);
	void loadTextures();
	void unloadTextures();
	GLfloat getValue();
	void increase(GLfloat increment);
	void decrcease(GLfloat decrement);
	void draw();
};

#endif // !SLIDER_H
