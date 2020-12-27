#ifndef SLIDER_H
#define SLIDER_H
#include "Texture.h"
#include <vector>
#include <GL/freeglut.h>

class Slider{
public:
	enum Orientation {
		HORIZONTAL, VERTICAL
	};
private:
	GLfloat value;
	Orientation orientation;
	GLfloat width;
	GLfloat height;
	std::vector<GLfloat> squarePos;
	std::vector<GLfloat> squareCoord = {
		1,1,0,
		-1,1,0,
		-1,-1,0,
		1,-1,0,
	};
	std::vector<GLfloat> squareColours = {
		1,0.8f,0,
		1,0.8f,0,
		1,0.8f,0,
		1,0.8f,0,
	};
	std::vector<GLfloat> vertCoord = {
		1,1,0,
		-1,1,0,
		-1,-1,0,
		1,-1,0,
	};
	std::vector<GLfloat> textCoord = {
		1,1,
		0,1,
		0,0,
		1,0,
	};
	std::vector<GLfloat> vertNormals = {
	0,0,1,
	0,0,1,
	0,0,1,
	0,0,1,
	};
	static std::vector<Texture*> textures;
public:
	Slider(Orientation _orientation, GLfloat _width, GLfloat _height);
	static void loadTextures();
	static void unloadTextures();
	GLfloat getValue(GLfloat lowerBound = -1, GLfloat upperBound = 1);
	void increase(GLfloat increment);
	void decrease(GLfloat decrement);
	void draw(GLfloat positionX, GLfloat positionY, GLfloat scale);
};

#endif // !SLIDER_H
