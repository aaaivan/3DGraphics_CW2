#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "Wall.h"
#include "Ball.h"
#include "Slider.h"
#include <GL/freeglut.h>


class GameManager {
	std::vector<Wall> walls;
	Ball ball;
	GLint points;
	GLint attemptsLeft;
	Slider horizontalSlider;
	Slider verticalSlider;
public:
	GameManager();
	//~GameManager();
	static void loadTextures();
	static void unloadTextures();
	void update(GLfloat time);
	void restart();
	void draw();
	void drawScore();
};

#endif // !GAME_MANAGER_H
