#ifndef TARGET_H
#define TARGET_H
#include "Texture.h"
#include <GL/freeglut.h>
#include <vector>

class Target {
public:
	enum Points {
		ZERO, TEN, TWENTY, THIRTY
	};
private:
	std::vector<GLfloat> position;
	GLfloat size;
	GLfloat angle_azim, angle_polar;
	Points points;
	static std::vector<Texture*> textures;
	std::vector<GLfloat> vertCoord = {
		1,1,0.001f,
		-1,1,0.001f,
		-1,-1,0.001f,
		1,-1,0.001f,
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
public:
	Target(std::vector<GLfloat> _position, Points _points, GLfloat _angle_azim, GLfloat _angle_polar=0);
	static void loadTextures();
	static void unloadTextures();
	std::vector<GLfloat> getPosition();
	GLfloat getRadius();
	void deactivate();
	GLint getPoints();
	void draw();
};

#endif // !TARGET_H


