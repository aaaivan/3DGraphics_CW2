#include "Grass.h"

Texture* Grass::texture = nullptr;

Grass::Grass(GLfloat _width, GLfloat _length):
width(_width), length(_length){
	for (int i = 0; i < vertCoord.size(); i += 3)
		vertCoord[i] *= width / 2;
	for (int i = 2; i < vertCoord.size(); i += 3)
		vertCoord[i] *= length;
}

void Grass::loadTexture() {
	texture = new Texture("../Textures/grass.tga");
}

void Grass::unloadTexture() {
	delete texture;
	texture = nullptr;
}

void Grass::draw(){
	glPushMatrix();
	texture->bind();
	glVertexPointer(3, GL_FLOAT, 0, &vertCoord[0]);
	glNormalPointer(GL_FLOAT, 0, &vertNormals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &textCoord[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	texture->unbind();
	glPopMatrix();
}
