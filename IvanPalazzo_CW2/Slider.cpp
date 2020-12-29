#include "Slider.h"
#include <algorithm>

std::vector<Texture*> Slider::textures;

Slider::Slider(Orientation _orientation, GLfloat _width, GLfloat _height):
	value(0), orientation(_orientation), width(_width), height(_height),
	squarePos({0,0}) {
	for (int i = 0; i < vertCoord.size(); i += 3)
		vertCoord[i] *= width / 2.0f;
	for (int i = 1; i < vertCoord.size(); i += 3)
		vertCoord[i] *= height / 2.0f;
	GLfloat thickness = std::min(width, height);
	if (orientation == Orientation::HORIZONTAL) {
		for (int i = 0; i < squareCoord.size(); i += 3)
			squareCoord[i] *= thickness / 8.0f;
		for (int i = 1; i < squareCoord.size(); i += 3)
			squareCoord[i] *= thickness / 2.0f;
	}
	else {
		for (int i = 0; i < squareCoord.size(); i += 3)
			squareCoord[i] *= thickness / 2.0f;
		for (int i = 1; i < squareCoord.size(); i += 3)
			squareCoord[i] *= thickness / 8.0f;
	}
}

void Slider::loadTextures() {
	textures.push_back(new Texture("../Textures/barH.tga"));
	textures.push_back(new Texture("../Textures/barV.tga"));
}

void Slider::unloadTextures(){
	for (int i = 0; i < textures.size(); i++) {
		delete textures[i];
		textures[i] = nullptr;
	}
}

GLfloat Slider::getValue(GLfloat lowerBound, GLfloat upperBound) {
	return lowerBound + (upperBound-lowerBound)*(value+1)/2;
}

void Slider::changeValue(GLfloat increment) {
	value += increment;
	if (value > 1.0f)
		value = 1.0f;
	else if (value < -1.0f)
		value = -1.0f;
	if (orientation == Orientation::HORIZONTAL)
		squarePos[0] = width / 2 * value;
	else
		squarePos[1] = height / 2 * value;
}

void Slider::draw(GLfloat positionX, GLfloat positionY, GLfloat scale) {
	glPushMatrix();
	glTranslatef(positionX, positionY, 0);
	glScalef(scale, scale, scale);

	textures[orientation]->bind();
	glVertexPointer(3, GL_FLOAT, 0, &vertCoord[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &textCoord[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	textures[orientation]->unbind();

	glLoadIdentity();
	glTranslatef(positionX + squarePos[0], positionY + squarePos[1], 0);
	glScalef(scale, scale, scale);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, &squareColours[0]);
	glVertexPointer(3, GL_FLOAT, 0, &squareCoord[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glPopMatrix();
}
