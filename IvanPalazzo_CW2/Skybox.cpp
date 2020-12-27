#include "Skybox.h"

Texture* Skybox::texture=nullptr;

Skybox::Skybox(GLfloat _size, GLfloat _angularSpeed):
size(_size), angularSpeed(_angularSpeed), angle(10) {
	for (int i = 0; i < vertCoord.size(); i++)
		vertCoord[i] *= size / 2.0f;
}

void Skybox::loadTexture(){
	texture = new Texture("../Textures/skybox.tga");
}

void Skybox::unloadTexture(){
	delete texture;
	texture = nullptr;
}

void Skybox::Update(GLfloat time) {
	angle += time * angularSpeed;
	if (angle >= 360.0f)
		angle -= 360.0f;
	else if(angle<0)
		angle += 360.0f;
}

void Skybox::draw() {
	glPushMatrix();
	glRotatef(angle, 0, 1, 0);

	texture->bind();
	glVertexPointer(3, GL_FLOAT, 0, &vertCoord[0]);
	glNormalPointer(GL_FLOAT, 0, &vertNormals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &textCoord[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	texture->unbind();
	glPopMatrix();
}
