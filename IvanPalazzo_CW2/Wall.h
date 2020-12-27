#ifndef WALL_H
#define WALL_H
#include "Texture.h"
#include "Target.h"
#include "Ball.h"
#include <GL/freeglut.h>
#include <vector>
#include <cmath>

class Wall
{
	GLfloat width, height;
	std::vector<GLfloat> center;
	std::vector<GLfloat> normal;
	GLfloat angle;
	std::vector<Target*> targets;
	static Texture* texture;
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

public:
	Wall(GLfloat _width, GLfloat _height, std::vector<GLfloat> _center, GLfloat _angle);
	~Wall();
	static void loadTexture();
	static void unloadTexture();
	void addTarget(GLfloat wallCoordX, GLfloat wallCoordY, Target::Points points, GLint* targetCounter);
	GLboolean checkCollision(Ball* ball, GLint* pointsGained);
	void draw();
};

#endif // !WALL_H
