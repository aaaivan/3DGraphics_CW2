#include "Ball.h"
#include "Lighting.h"
#include <cmath>

Texture* Ball::texture = nullptr;

//constructor: the ball is position at the initPosition and it is not moving
Ball::Ball(GLfloat _radius, std::vector<GLfloat> _initPosition, GLfloat _speed, GLfloat _angularSpeed):
	radius(_radius), initPosition(_initPosition), position(initPosition),
	velocity(3, 0), speed(_speed), angle(0), angularSpeed(_angularSpeed),
	moving(false), qobj(gluNewQuadric()) {
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricTexture(qobj, GL_TRUE);
}

//destructor: relese memory allocated by gluNewQuadric()
Ball::~Ball() {
	gluDeleteQuadric(qobj);
}

//load ball texture for rendering
void Ball::loadTexture() {
	texture = new Texture("../Textures/football.tga");
}

//delete ball texture from memory
void Ball::unloadTexture() {
	delete texture;
	texture = nullptr;
}

//position of the ball relative to the vector passed as the argument
std::vector<GLfloat> Ball::relPosition(std::vector<GLfloat> newOrigin) const {
	std::vector<GLfloat> relPos;
	relPos.push_back(position[0] - newOrigin[0]);
	relPos.push_back(position[1] - newOrigin[1]);
	relPos.push_back(position[2] - newOrigin[2]);
	return relPos;
}

//position of the ball relative to the initial position
std::vector<GLfloat> Ball::relToInitPosition() const {
	std::vector<GLfloat> relPos;
	relPos.push_back(position[0] - initPosition[0]);
	relPos.push_back(position[1] - initPosition[1]);
	relPos.push_back(position[2] - initPosition[2]);
	return relPos;
}

GLfloat Ball::getRadius() const {
	return radius;
}

//update position and orientation of the ball
void Ball::update(GLfloat time) {
	if (moving) {
		position[0] += velocity[0] * time;
		position[1] += velocity[1] * time;
		position[2] += velocity[2] * time;
		angle -= angularSpeed * time;
		if (angle < 0.0f)
			angle += 360.0f;
	}
}

//shoot the ball if is not moving
GLfloat Ball::shoot(GLfloat horiz, GLfloat vert){
	if (!moving) {
		velocity[0] = horiz;
		velocity[1] = vert;
		velocity[2] = -1;
		//rescale velocity vector to have its magnitude equal to speed
		GLfloat magnitude = 0;
		for (int i = 0; i < 3; i++)
			magnitude += velocity[i] * velocity[i];
		magnitude = sqrtf(magnitude);
		for (int i = 0; i < 3; i++)
			velocity[i] *= speed / magnitude;
		moving = true;
		return true;
	}
	//ball already moving
	return false;
}

//bring ball back to initial position
void Ball::reset(){
	for (int i = 0; i < 3; i++)
		position[i] = initPosition[i];
	angle = 0;
	moving = false;
}

//draw ball
void Ball::draw() {
	//lighting
	glEnable(GL_LIGHT0); //spotlight for highlights on the ball
	glMaterialfv(GL_FRONT, GL_SPECULAR, Lighting::m_specularBall);
	glMaterialf(GL_FRONT, GL_SHININESS, Lighting::shininess_ball);
	//transformations
	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);
	glRotatef(angle, -velocity[2], 0, velocity[0]);
	//drawing
	texture->bind();
	gluSphere(qobj, radius, 50, 30);
	texture->unbind();
	glPopMatrix();
	//disable spotlight
	glMaterialf(GL_FRONT, GL_SHININESS, 1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Lighting::m_specular);
	glDisable(GL_LIGHT0);
}
