#include "Plant.h"

std::vector<Texture*> Plant::textures;

Plant::Plant(GLfloat _width, GLfloat _height, std::vector<GLfloat> _position, GLfloat _angle, Type _type):
width(_width), height(_height), position(_position), angle(_angle), type(_type){
	for (int i = 0; i < vertCoord.size(); i += 3)
		vertCoord[i] *= width / 2.0f;
	for (int i = 1; i < vertCoord.size(); i += 3)
		vertCoord[i] *= height / 2.0f;
}

void Plant::loadTextures(){
	textures.push_back(new Texture("../Textures/palm.tga"));
	textures.push_back(new Texture("../Textures/yellowFlower.tga"));
	textures.push_back(new Texture("../Textures/orangeFlower.tga"));
}

void Plant::unloadTextures(){
	for (int i = 0; i < textures.size(); i++) {
		delete textures[i];
		textures[i] = nullptr;
	}
}

void Plant::draw(){
	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);
	glRotatef(angle, 0, 1, 0);

	textures[type]->bind();
	glVertexPointer(3, GL_FLOAT, 0, &vertCoord[0]);
	glNormalPointer(GL_FLOAT, 0, &vertNormals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &textCoord[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	textures[type]->unbind();
	glPopMatrix();

}
