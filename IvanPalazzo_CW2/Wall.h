#ifndef WALL_H
#define WALL_H
#include "Texture.h"
#include "Target.h"
#include "Ball.h"
#include "Globals.h"
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
		//front
		1,1,0,
		-1,1,0,
		-1,-1,0,
		1,-1,0,
		//top
		-1,1,0,
		1,1,0,
		1,1,-WALL_THICKNESS,
		-1,1,-WALL_THICKNESS,
	};
	std::vector<GLfloat> textCoord = {
		//front
		1,1,
		0,1,
		0,0,
		1,0,
		//top
		0,0,
		1,0,
		1,0.2f,
		0,0.2f,
	};
	std::vector<GLfloat> vertNormals = {
		//front
		0,0,1,
		0,0,1,
		0,0,1,
		0,0,1,
		//top
		0,1,0,
		0,1,0,
		0,1,0,
		0,1,0,
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
