#ifndef BALL_H
#define BALL_H
#include "Slider.h"
#include "Texture.h"
#include <string>
#include <vector>
#include <GL/freeglut.h>

class Ball
{
	std::vector<GLfloat> initPosition;
	GLfloat radius;
	std::vector<GLfloat> position;
	std::vector<GLfloat> velocity;
	GLfloat speed, angularSpeed;
	GLfloat angle;
	GLboolean rotateCW, moving;
	GLUquadricObj* qobj;
	static Texture* texture;
public:
	Ball(GLfloat _radius, std::vector<GLfloat> _initPosition, GLfloat _speed, GLfloat _angularSpeed);
	~Ball();
	static void loadTextures();
	static void unloadTexture();
	std::vector<GLfloat> relPosition(std::vector<GLfloat> newOrigin);
	GLfloat getRadius();
	void update(GLfloat time);
	void shoot(Slider* horiz, Slider* vert);
	void reset();
	void draw();
};

#endif // !BALL_H