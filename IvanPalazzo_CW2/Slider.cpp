#include "Slider.h"

Slider::Slider(Orientation _orientation, GLfloat _width, GLfloat _height):
	value(0), orientation(_orientation), width(_width), height(_height) {
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

GLfloat Slider::getValue() {
	return value;
}

void Slider::increase(GLfloat increment) {
	value += increment;
	if (value > 1.0f)
		value = 1.0f;
}

void Slider::decrcease(GLfloat decrement) {
	value -= decrement;
	if (value < -1.0f)
		value = -1.0f;
}

void Slider::draw() {

}
