#include "Target.h"
#include "Globals.h"

std::vector<Texture*> Target::textures;

//constructor: initialize variables
Target::Target(std::vector<GLfloat> _position, Points _points, GLfloat _angle_azim, GLfloat _angle_polar):
position(_position), points(_points), size(0), angle_azim(_angle_azim), angle_polar(_angle_polar) {
	switch (_points)
	{
	case TEN:
		size = TARGET10_SIZE;
		break;
	case TWENTY:
		size = TARGET20_SIZE;
		break;
	case THIRTY:
		size = TARGET30_SIZE;
		break;
	default:
		size = TARGET30_SIZE;
		break;
	}
	//rescale vertex array
	for (int i = 0; i < vertCoord.size(); i += 3)
		vertCoord[i] *= size / 2;
	for (int i = 1; i < vertCoord.size(); i += 3)
		vertCoord[i] *= size / 2;
}

//load textures for rendering
void Target::loadTextures() {
	textures.push_back(new Texture("../Textures/targetDull.tga"));
	textures.push_back(new Texture("../Textures/targetGreen.tga"));
	textures.push_back(new Texture("../Textures/targetBlue.tga"));
	textures.push_back(new Texture("../Textures/targetRed.tga"));
}

//delete textures from memory
void Target::unloadTextures() {
	for (int i = 0; i < textures.size(); i++) {
		delete textures[i];
		textures[i] = nullptr;
	}
}


std::vector<GLfloat> Target::getPosition() const {
	return position;
}

GLfloat Target::getRadius() const {
	return size/2;
}

void Target::deactivate(){
	points = Points::ZERO;
}

GLint Target::getPoints() const {
	switch (points){
	case ZERO:
		return 0;
	case TEN:
		return 10;
	case TWENTY:
		return 20;
	case THIRTY:
		return 30;
	default:
		return 0;
	}
}

void Target::draw(){
	//transformations
	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);
	glRotatef(angle_azim, 0, 1, 0);
	glRotatef(angle_polar, 1, 0, 0);
	//drawing
	textures[points]->bind();
	glVertexPointer(3, GL_FLOAT, 0, &vertCoord[0]);
	glNormalPointer(GL_FLOAT, 0, &vertNormals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &textCoord[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	textures[points]->unbind();
	glPopMatrix();
}
