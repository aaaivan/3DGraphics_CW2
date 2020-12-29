#include "Wall.h"

Texture* Wall::texture=nullptr;

//Constructor: initialize objects and variables
Wall::Wall(GLfloat _width, GLfloat _height, std::vector<GLfloat> _center, GLfloat _angle):
width(_width), height(_height), center(_center), angle(_angle), normal(), targets(){
	//specify normal vector to the plane of the wall
	normal.push_back(sinf(angle * M_PI / 180));
	normal.push_back(0);
	normal.push_back(cosf(angle * M_PI / 180));
	//rescale vertex array
	for (int i = 0; i < vertCoord.size(); i += 3)
		vertCoord[i] *= width / 2;
	for (int i = 1; i < vertCoord.size(); i += 3)
		vertCoord[i] *= height / 2;
}

//destructor: delete memory allocated for the targets
Wall::~Wall() {
	for (int i = 0; i < targets.size(); i++)
		delete targets[i];
}

//load textures for rendering
void Wall::loadTexture() {
	texture = new Texture("../Textures/wall.tga");
	Target::loadTextures();
}

//delete texture from memory
void Wall::unloadTexture() {
	delete texture;
	texture = nullptr;
	Target::unloadTextures();
}

//add a target to the wall at the specified wall coordinates, where (0,0) is the center of the wall.
//Also, if targetCounter is not nullptr, increase the int pointed to by 1;
void Wall::addTarget(GLfloat wallCoordX, GLfloat wallCoordY, Target::Points points, GLint* targetCounter) {
	std::vector<GLfloat> targetPos = {
		center[0] + wallCoordX * cosf(angle * M_PI / 180),
		center[1] + wallCoordY,
		center[2] - wallCoordX * sinf(angle * M_PI / 180)
	};
	//add new target to the list of targets on the wall
	targets.push_back(new Target(targetPos, points, angle, 0));
	if (targetCounter)
		*targetCounter += 1;
}

//check for collisions between the ball and wall. Return true is the wall has been hit.
//If a target is hit, set *pointsGained to the corresponding value; set it to 0 otherwise.
GLboolean Wall::checkCollision(Ball* b, GLint* pointsGained) {
	*pointsGained = 0;
	//position of the ball relative to the wall
	std::vector<GLfloat>relToWall = b->relPosition(center);
	//distance of the ball from the wall
	GLfloat distToWall =
		relToWall[0] * normal[0] +
		relToWall[1] * normal[1] +
		relToWall[2] * normal[2];
	if (distToWall < b->getRadius()) { //collision with the wall detected
		//check collision with targets on this wall
		for (Target* t : targets) {
			//position of the ball relative to the center of the target
			std::vector<GLfloat>relToTarget = b->relPosition(t->getPosition());
			//distance of the ball from the center of the
			GLfloat distToTargetSquared =
				relToTarget[0] * relToTarget[0] +
				relToTarget[1] * relToTarget[1] +
				relToTarget[2] * relToTarget[2];
			//Pythagoras's theorem
			GLfloat legSquared = distToTargetSquared - distToWall * distToWall;
			if (legSquared <= t->getRadius() * t->getRadius()) { //the ball has hit the target
				GLint points = t->getPoints();
				t->deactivate();
				*pointsGained = points;
				break;
			}
		}
		//the ball has hit the wall
		return true;
	}
	//the ball has not hit the wall
	return false;
}

void Wall::draw() {
	//transformations
	glPushMatrix();
	glTranslatef(center[0], center[1], center[2]);
	glRotatef(angle, 0, 1, 0);
	//drawing wall
	texture->bind();
	glVertexPointer(3, GL_FLOAT, 0, &vertCoord[0]);
	glNormalPointer(GL_FLOAT, 0, &vertNormals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &textCoord[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	texture->unbind();
	glPopMatrix();
	//draw targets
	for (Target* t : targets)
		t->draw();
}
