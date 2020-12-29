#ifndef PROPS_H
#define PROPS_H
#include "Grass.h"
#include "Plant.h"
#include "Target.h"
#include "Globals.h"
#include <GL/freeglut.h>
#include <vector>

//contains the decorative elements of the scene
//with no collision detection
class Props{
	Grass grass;
	std::vector<Plant> plants;
	Target startPos;
public:
	Props();
	static void loadTextures();
	static void unloadTextures();
	void draw();
};

#endif // !PROPS_H


