#include "Ball.h"
#include "Globals.h"
#include <cmath>

Texture* Ball::texture = nullptr;

Ball::Ball(GLfloat _radius, std::vector<GLfloat> _initPosition, GLfloat _speed, GLfloat _angularSpeed):
	radius(_radius), initPosition(_initPosition), position(initPosition),
	velocity(3, 0), speed(_speed), angle(0), angularSpeed(_angularSpeed),
	rotateCW(true), moving(false), qobj(gluNewQuadric()) {
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricTexture(qobj, GL_TRUE);
}

Ball::~Ball() {
	gluDeleteQuadric(qobj);
}

void Ball::loadTextures() {
	texture = new Texture("../Textures/football.tga");
}

void Ball::unloadTexture() {
	delete texture;
	texture = nullptr;
}

std::vector<GLfloat> Ball::relPosition(std::vector<GLfloat> newOrigin) {
	std::vector<GLfloat> relPos;
	relPos.push_back(position[0] - newOrigin[0]);
	relPos.push_back(position[1] - newOrigin[1]);
	relPos.push_back(position[2] - newOrigin[2]);
	return relPos;
}

GLfloat Ball::getRadius() {
	return radius;
}

void Ball::update(GLfloat time) {
	if (moving) {
		position[0] += velocity[0] * time;
		position[1] += velocity[1] * time;
		position[2] += velocity[2] * time;
		if (rotateCW) {
			angle += angularSpeed * time;
			if (angle >= 2 * M_PI)
				angle -= 2 * M_PI;
		}
		else {
			angle -= angularSpeed * time;
			if (angle < 0)
				angle += 2 * M_PI;
		}
	}
}

void Ball::shoot(Slider* horiz, Slider* vert){
	velocity[0] = horiz->getValue();
	velocity[1] = vert->getValue();
	velocity[2] = -1;
	//rescale velocity vector to have magnitude equal to speed
	GLfloat magnitude = 0;
	for (int i = 0; i < 3; i++)
		magnitude += velocity[i] * velocity[i];
	magnitude = sqrtf(magnitude);
	for (int i = 0; i < 3; i++)
		velocity[i] *= speed/magnitude;

	if (velocity[1] >= 0)
		rotateCW = true;
	else
		rotateCW = false;
	moving = true;
}

void Ball::reset()
{
	for (int i = 0; i < 3; i++)
		position[i] = initPosition[i];
	angle = 0;
	moving = false;
}

void Ball::draw() {
	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);
	glRotatef(angle, 0, 1, 0);
	texture->bind();
	gluSphere(qobj, 1, 50, 50);
	texture->unbind();
	glPopMatrix();
}
