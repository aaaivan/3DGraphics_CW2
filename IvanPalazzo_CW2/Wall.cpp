#include "Wall.h"

Texture* Wall::texture=nullptr;

Wall::Wall(GLfloat _width, GLfloat _height, std::vector<GLfloat> _center, GLfloat _angle):
width(_width), height(_height), center(_center), angle(_angle), normal(), targets(){
	normal.push_back(sinf(angle * M_PI / 180));
	normal.push_back(0);
	normal.push_back(cosf(angle * M_PI / 180));
	for (int i = 0; i < vertCoord.size(); i += 3)
		vertCoord[i] *= width / 2;
	for (int i = 1; i < vertCoord.size(); i += 3)
		vertCoord[i] *= height / 2;
}

Wall::~Wall() {
	for (int i = 0; i < targets.size(); i++)
		delete targets[i];
}

void Wall::loadTexture() {
	texture = new Texture("../Textures/wall.tga");
	Target::loadTextures();
}

void Wall::unloadTexture() {
	delete texture;
	texture = nullptr;
	Target::unloadTextures();
}

void Wall::addTarget(GLfloat wallCoordX, GLfloat wallCoordY, Target::Points points, GLint* targetCounter) {
	std::vector<GLfloat> targetPos = {
		center[0] + wallCoordX * cosf(angle * M_PI / 180),
		center[1] + wallCoordY,
		center[2] - wallCoordX * sinf(angle * M_PI / 180)
	};
	targets.push_back(new Target(targetPos, points, angle, 0));
	if (targetCounter)
		*targetCounter += 1;
}

GLboolean Wall::checkCollision(Ball* b, GLint* pointsGained) {
	*pointsGained = 0;
	std::vector<GLfloat>relToWall = b->relPosition(center);
	GLfloat distToWall =
		relToWall[0] * normal[0] +
		relToWall[1] * normal[1] +
		relToWall[2] * normal[2];
	if (distToWall < b->getRadius()) {
		for (Target* t : targets) {
			std::vector<GLfloat>relToTarget = b->relPosition(t->getPosition());
			GLfloat distToTargetSquared = 
				relToTarget[0] * relToTarget[0] +
				relToTarget[1] * relToTarget[1] +
				relToTarget[2] * relToTarget[2];
			GLfloat legSquared = distToTargetSquared - distToWall * distToWall;
			if (legSquared <= t->getRadius() * t->getRadius()) {
				GLint points = t->getPoints();
				t->deactivate();
				*pointsGained = points;
				break;
			}
		}
		return true;
	}
	return false;
}

void Wall::draw() {
	glPushMatrix();
	glTranslatef(center[0], center[1], center[2]);
	glRotatef(angle, 0, 1, 0);

	texture->bind();
	glVertexPointer(3, GL_FLOAT, 0, &vertCoord[0]);
	glNormalPointer(GL_FLOAT, 0, &vertNormals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &textCoord[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	texture->unbind();
	glPopMatrix();
	for (Target* t : targets)
		t->draw();
}
