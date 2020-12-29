#ifndef PLANT_H
#define PLANT_H
#include "Texture.h"
#include <GL/freeglut.h>
#include <vector>

class Plant{
public:
	enum Type {
		PALM, YELLOW_FLOWER, ORANGE_FLOWER
	};
private:
	GLfloat width, height;
	std::vector<GLfloat> position;
	std::vector<GLfloat> vertCoord = {
		1,1,0,
		-1,1,0,
		-1,-1,0,
		1,-1,0,
	};
	std::vector<GLfloat> textCoord = {
		1,1,
		0,1,
		0,0,
		1,0,
	};
	std::vector<GLfloat> vertNormals = {
		0,0,1,
		0,0,1,
		0,0,1,
		0,0,1,
	};
	GLfloat angle; //rotation about the Y axis
	Type type; //type of plant
	static std::vector<Texture*> textures;
public:
	Plant(GLfloat _width, GLfloat _height, std::vector<GLfloat> _position, GLfloat _angle, Type _type);
	static void loadTextures();
	static void unloadTextures();
	void draw();
};

#endif // !PLANT_H
