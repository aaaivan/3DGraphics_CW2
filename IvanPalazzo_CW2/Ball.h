#ifndef BALL_H
#define BALL_H
#include "Slider.h"
#include "Texture.h"
#include "Globals.h"
#include <string>
#include <vector>
#include <GL/freeglut.h>

class Ball {
	std::vector<GLfloat> initPosition;
	GLfloat radius;
	std::vector<GLfloat> position;
	std::vector<GLfloat> velocity;
	GLfloat speed, angularSpeed;
	GLfloat angle;
	GLboolean moving;
	GLUquadricObj* qobj; //3d model
	static Texture* texture;
public:
	Ball(GLfloat _radius, std::vector<GLfloat> _initPosition, GLfloat _speed, GLfloat _angularSpeed);
	~Ball();
	static void loadTexture();
	static void unloadTexture();
	std::vector<GLfloat> relPosition(std::vector<GLfloat> newOrigin) const;
	std::vector<GLfloat> relToInitPosition() const;
	GLfloat getRadius() const;
	void update(GLfloat time);
	GLfloat shoot(GLfloat horiz, GLfloat vert);
	void reset();
	void draw();
};

#endif // !BALL_H